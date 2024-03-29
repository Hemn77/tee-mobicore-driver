/** @addtogroup NQ
 * @{
 * Notifications inform the MobiCore runtime environment that information is
 * pending in a WSM buffer.
 * The Trustlet Connector (TLC) and the corresponding trustlet also utilize
 * this buffer to notify each other about new data within the
 * Trustlet Connector Interface (TCI).
 *
 * The buffer is set up as a queue, which means that more than one
 * notification can be written to the buffer before the switch to the other
 * world is performed. Each side therefore facilitates an incoming and an
 * outgoing queue for communication with the other side.
 *
 * Notifications hold the session ID, which is used to reference the
 * communication partner in the other world.
 * So if, e.g., the TLC in the normal world wants to notify his trustlet
 * about new data in the TLC buffer
 *
 * @file
 * Notification queue declarations.
 *
 * <!-- Copyright Giesecke & Devrient GmbH 2009-2012 -->
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *	notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *	notice, this list of conditions and the following disclaimer in the
 *	documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *	products derived from this software without specific prior
 *	written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef NQ_H_
#define NQ_H_

/** \name NQ Size Defines
 * Minimum and maximum count of elements in the notification queue.
 * @{ */
#define MIN_NQ_ELEM 1   /**< Minimum notification queue elements. */
#define MAX_NQ_ELEM 64 /**< Maximum notification queue elements. */
/** @} */

/** \name NQ Length Defines
 * Minimum and maximum notification queue length.
 * @{ */
/**< Minimum notification length (in bytes). */
#define MIN_NQ_LEN (MIN_NQ_ELEM * sizeof(notification_t))
/**< Maximum notification length (in bytes). */
#define MAX_NQ_LEN (MAX_NQ_ELEM * sizeof(notification_t))
/** @} */

/** \name Session ID Defines
 * Standard Session IDs.
 * @{ */
/**< MCP session ID is used when directly communicating with the MobiCore
 * (e.g. for starting and stopping of trustlets). */
#define SID_MCP	   0
/**< Invalid session id is returned in case of an error. */
#define SID_INVALID   0xffffffff
/** @} */

/** Notification data structure. */
struct notification_t {
	uint32_t sessionId; /**< Session ID. */
	int32_t payload;	/**< Additional notification information. */
};

/** Notification payload codes.
 * 0 indicated a plain simple notification,
 * a positive value is a termination reason from the task,
 * a negative value is a termination reason from MobiCore.
 * Possible negative values are given below.
 */
enum notificationPayload_t {
	/**< task terminated, but exit code is invalid */
	ERR_INVALID_EXIT_CODE   = -1,
	/**< task terminated due to session end, no exit code available */
	ERR_SESSION_CLOSE	   = -2,
	/**< task terminated due to invalid operation */
	ERR_INVALID_OPERATION   = -3,
	/**< session ID is unknown */
	ERR_INVALID_SID		 = -4,
	/**<  session is not active */
	ERR_SID_NOT_ACTIVE	  = -5
};

/** Declaration of the notification queue header.
 * layout as specified in the data structure specification.
 */
struct notificationQueueHeader_t {
	uint32_t writeCnt;  /**< Write counter. */
	uint32_t readCnt;   /**< Read counter. */
	uint32_t queueSize; /**< Queue size. */
};

/** Queue struct which defines a queue object.
 * The queue struct is accessed by the queue<operation> type of
 * function. elementCnt must be a power of two and the power needs
 * to be smaller than power of uint32_t (obviously 32).
 */
struct notificationQueue_t {
	/**< Queue header. */
	struct notificationQueueHeader_t hdr;
	/**< Notification elements. */
	struct notification_t notification[MIN_NQ_ELEM];
} ;

#endif /** NQ_H_ */

/** @} */
