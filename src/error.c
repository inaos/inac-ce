/*
 * Copyright INAOS GmbH, Thalwil, 2012-2018. All rights reserved
 *
 * This software is the confidential and proprietary information of INAOS GmbH
 * ("Confidential Information"). You shall not disclose such Confidential
 * Information and shall use it only in accordance with the terms of the
 * license agreement you entered into with INAOS GmbH.
 */
#include <libinac-ce/lib.h>
#include "config.h"

/* Error message length */
#define __INA_ERROR_MSGLEN  1024

INA_TLS(ina_rc_t) __rc = INA_SUCCESS;
static INA_TLS(ina_err_subject_cb_t) __dict_cb = NULL;
static INA_TLS(ina_str_t)            __errmsg  = NULL;
static char                          __msgbuf[__INA_ERROR_MSGLEN+32];

INA_API(ina_rc_t) ina_err_init(void)
{
    INA_INIT_GUARD();
    __errmsg = ina_str_assign_buf(__msgbuf, __INA_ERROR_MSGLEN+32);
    return INA_SUCCESS;
}

INA_API(void) ina_err_destroy(void)
{
    INA_DESTROY_GUARD();
}


INA_API(ina_err_subject_cb_t) ina_err_register_dict(ina_err_subject_cb_t cb)
{
    ina_err_subject_cb_t old_cb = __dict_cb;
    __dict_cb = cb;
    return old_cb;
}

static const char* __ina_get_subject(int id) {
    switch (id) {
        case INA_ES_NONE: return "";
        case INA_ES_ACCESS: return "ACCESS";
        case INA_ES_ARGUMENT: return "ARGUMENT";
        case INA_ES_COMPRESSION: return "COMPRESSION";
        case INA_ES_DECOMPRESSION: return "DECOMPRESSION";
        case INA_ES_DESCRIPTOR: return "DESCRIPTOR";
        case INA_ES_DEVICE: return "DEVICE";
        case INA_ES_DIRECTORY: return "DIRECTORY";
        case INA_ES_FILE: return "FILE";
        case INA_ES_FUNCTION: return "FUNCTION";
        case INA_ES_HANDLE: return "HANDLE";
        case INA_ES_INPUT: return "INPUT";
        case INA_ES_IO: return "IO";
        case INA_ES_LIMIT: return "LIMIT";
        case INA_ES_MEMORY: return "MEMORY";
        case INA_ES_OBJECT: return "OBJECT";
        case INA_ES_POSITION: return "POSITION";
        case INA_ES_POOL: return "POOL";
        case INA_ES_SCRIPT: return "SCRIPT";
        case INA_ES_SIZE: return "SIZE";
        case INA_ES_STRING: return "STRING";
        case INA_ES_TYPE: return "TYPE";
        case INA_ES_VERSION: return "VERSION";
        case INA_ES_STATE: return "STATE";
        case INA_ES_CONFIGURATION: return "CONFIGURATION";
        case INA_ES_SECTION: return "SECTION";
        case INA_ES_KEY: return "KEY";
        case INA_ES_ENUMERATION: return "ENUMERATION";
        case INA_ES_READ: return "READ";
        case INA_ES_WRITE: return "WRITE";
        case INA_ES_OPTION: return "OPTION";
        case INA_ES_BUFFER: return "BUFFER";
        case INA_ES_ADDRESS: return "ADDRESS";
        case INA_ES_MAC: return "MAC";
        case INA_ES_PROCESS: return "PROCESS";
        case INA_ES_PATTERN: return "PATTERN";
        case INA_ES_SEMAPHORE: return "SEMAPHORE";
        case INA_ES_OPERATION: return "OPERATION";
        case INA_ES_TIME: return "TIME";
        case INA_ES_HOST: return "HOST";
        case INA_ES_TEXT: return "TEXT";
        case INA_ES_API: return "API";
        default:
            if (__dict_cb != NULL) {
                return  __dict_cb(id);
            }
            return "??";
    }
}

INA_API(const char*) ina_err_strerror(ina_rc_t rc)
{
    const char *neg = "", *adj = "";
    const char *noun =  __ina_get_subject(INA_RC_SUBJECT(rc));

    if (INA_SUCCEED(rc)) {
        ina_str_truncate(__errmsg, 0);
        return __errmsg;
    }

    if (rc & ( 1ULL << INA_RC_BIT_N )) {
        neg = "NOT";
    }

    switch (rc & ( 0xFFULL << INA_RC_BIT_C ) ) {
        default: break;
        case INA_ERR_A: adj = "A";break;
        case INA_ERR_ACK: adj = "ACK";break;
        case INA_ERR_ACTIVE: adj = "ACTIVE"; break;
        case INA_ERR_ALIGNED: adj = "ALIGNED"; break;
        case INA_ERR_ALLOWED: adj = "ALLOWED"; break;
        case INA_ERR_ASSIGNED: adj = "ASSIGNED";break;
        case INA_ERR_ATTACHED: adj = "ATTACHED"; break;
        case INA_ERR_ATTEMPTED: adj = "ATTEMPTED"; break;
        case INA_ERR_AUTHORIZED: adj = "AUTHORIZED"; break;
        case INA_ERR_AVAILABLE: adj = "AVAILABLE"; break;
        case INA_ERR_BAD: adj = "BAD"; break;
        case INA_ERR_BLOCKED: adj = "BLOCKED"; break;
        case INA_ERR_BROKEN: adj = "BROKEN"; break;
        case INA_ERR_BUILT: adj = "BUILT"; break;
        case INA_ERR_BUSY: adj = "BUSY"; break;
        case INA_ERR_CLOSED: adj = "CLOSED"; break;
        case INA_ERR_COMPILED: adj = "COMPILED"; break;
        case INA_ERR_COMPLETE: adj = "COMPLETE"; break;
        case INA_ERR_CONFLICTED: adj = "CONFLICTED"; break;
        case INA_ERR_CONNECTED: adj = "CONNECTED"; break;
        case INA_ERR_CONSTRUCTED: adj = "CONSTRUCTED"; break;
        case INA_ERR_CREATED: adj = "CREATED"; break;
        case INA_ERR_DEFINED: adj = "DEFINED"; break;
        case INA_ERR_DENIED: adj = "DENIED";break;
        case INA_ERR_DESTRUCTED: adj = "DESTRUCTED"; break;
        case INA_ERR_DETACHED: adj = "DETACHED"; break;
        case INA_ERR_DETECTED: adj = "DETECTED"; break;
        case INA_ERR_DOWN: adj = "DOWN"; break;
        case INA_ERR_DOWNLOADED: adj = "DOWNLOADED"; break;
        case INA_ERR_EMPTY: adj = "EMPTY"; break;
        case INA_ERR_ENHANCED: adj = "ENHANCED"; break;
        case INA_ERR_ENOUGH: adj = "ENOUGH"; break;
        case INA_ERR_EXCEEDED: adj = "EXCEEDED"; break;
        case INA_ERR_EXCHANGED: adj = "EXCHANGED"; break;
        case INA_ERR_EXECUTABLE: adj = "EXECUTABLE"; break;
        case INA_ERR_EXISTS: adj = "EXISTS"; break;
        case INA_ERR_EXPIRED: adj = "EXPIRED"; break;
        case INA_ERR_EXTENDED: adj = "EXTENDED"; break;
        case INA_ERR_FAILED: adj = "FAILED"; break;
        case INA_ERR_FALSE: adj = "FALSE"; break;
        case INA_ERR_FATAL: adj = "FATAL"; break;
        case INA_ERR_FORBIDDEN: adj = "FORBIDDEN"; break;
        case INA_ERR_FORMATTED: adj = "FORMATTED"; break;
        case INA_ERR_FOUND: adj = "FOUND"; break;
        case INA_ERR_FULL: adj = "FULL"; break;
        case INA_ERR_GONE: adj = "GONE"; break;
        case INA_ERR_GOOD: adj = "GOOD"; break;
        case INA_ERR_HALTED: adj = "HALTED"; break;
        case INA_ERR_HOLD: adj = "HOLD"; break;
        case INA_ERR_IDLE: adj = "IDLE"; break;
        case INA_ERR_ILLEGAL: adj = "ILLEGAL"; break;
        case INA_ERR_IMPLEMENTED: adj = "IMPLEMENTED"; break;
        case INA_ERR_IN_PROGRESS: adj = "IN PROGRESS"; break;
        case INA_ERR_IN_USE: adj = "IN USE"; break;
        case INA_ERR_INITIALIZED: adj = "INITIALIZED"; break;
        case INA_ERR_INSTALLED: adj = "INSTALLED"; break;
        case INA_ERR_INTERRUPTED: adj = "INTERRUPTED"; break;
        case INA_ERR_KNOWN: adj = "KNOWN"; break;
        case INA_ERR_LINKED: adj = "LINKED"; break;
        case INA_ERR_LOADED: adj = "LOADED"; break;
        case INA_ERR_LOCAL: adj = "LOCAL"; break;
        case INA_ERR_LOCKED: adj = "LOCKED"; break;
        case INA_ERR_LOOPED: adj = "LOOPED"; break;
        case INA_ERR_LOST: adj = "LOST"; break;
        case INA_ERR_MISSING: adj = "MISSING"; break;
        case INA_ERR_MOUNTED: adj = "MOUNTED"; break;
        case INA_ERR_NEEDED: adj = "NEEDED"; break;
        case INA_ERR_NO: adj = "NO"; break;
        case INA_ERR_NO_SUCH: adj = "NO SUCH"; break;
        case INA_ERR_OFF: adj = "OFF"; break;
        case INA_ERR_ON: adj = "ON"; break;
        case INA_ERR_ONLINE: adj = "ONLINE"; break;
        case INA_ERR_OPEN: adj = "OPEN"; break;
        case INA_ERR_ORDERED: adj = "ORDERED"; break;
        case INA_ERR_OUT_OF: adj = "OUT OF";break;
        case INA_ERR_OUT_OF_RANGE: adj = "OUT OF RANGE"; break;
        case INA_ERR_OVERFLOW: adj = "OVERFLOW"; break;
        case INA_ERR_PADDED: adj = "PADDED"; break;
        case INA_ERR_PERMITTED: adj = "PERMITTED"; break;
        case INA_ERR_PROCESSABLE: adj = "PROCESSABLE"; break;
        case INA_ERR_PROVIDED: adj = "PROVIDED"; break;
        case INA_ERR_REACHABLE: adj = "REACHABLE"; break;
        case INA_ERR_READABLE: adj = "READABLE"; break;
        case INA_ERR_RECEIVED: adj = "RECEIVED"; break;
        case INA_ERR_REFUSED: adj = "REFUSED"; break;
        case INA_ERR_REGISTERED: adj = "REGISTERED"; break;
        case INA_ERR_REJECTED: adj = "REJECTED"; break;
        case INA_ERR_RELEASED: adj = "RELEASED"; break;
        case INA_ERR_REMOTE: adj = "REMOTE"; break;
        case INA_ERR_RENDERABLE: adj = "RENDERABLE"; break;
        case INA_ERR_RESERVED: adj = "RESERVED"; break;
        case INA_ERR_RESET: adj = "RESET"; break;
        case INA_ERR_RESPONDING: adj = "RESPONDING"; break;
        case INA_ERR_RETRIED: adj = "RETRIED"; break;
        case INA_ERR_RIGHT: adj = "RIGHT"; break;
        case INA_ERR_RUNNING: adj = "RUNNING"; break;
        case INA_ERR_SENT: adj = "SENT"; break;
        case INA_ERR_SPECIFIED: adj = "SPECIFIED"; break;
        case INA_ERR_STALLED: adj = "STALLED"; break;
        case INA_ERR_STOPPED: adj = "STOPPED"; break;
        case INA_ERR_SUCEEDED: adj = "SUCEEDED"; break;
        case INA_ERR_SUITABLE: adj = "SUITABLE"; break;
        case INA_ERR_SUPPORTED: adj = "SUPPORTED"; break;
        case INA_ERR_SYNCHRONIZED: adj = "SYNCHRONIZED"; break;
        case INA_ERR_TERMINATED: adj = "TERMINATED"; break;
        case INA_ERR_THROWN: adj = "THROWN"; break;
        case INA_ERR_TIMED_OUT: adj = "TIMED OUT"; break;
        case INA_ERR_TOO_COMPLEX: adj = "TOO COMPLEX"; break;
        case INA_ERR_TOO_FEW: adj = "TOO FEW"; break;
        case INA_ERR_TOO_LARGE: adj = "TOO LARGE"; break;
        case INA_ERR_TOO_LONG: adj = "TOO LONG";break;
        case INA_ERR_TOO_MANY: adj = "TOO MANY"; break;
        case INA_ERR_TOO_MUCH: adj = "TOO MUCH"; break;
        case INA_ERR_TOO_SIMPLE: adj = "TOO SIMPLE"; break;
        case INA_ERR_TOO_SMALL: adj = "TOO SMALL"; break;
        case INA_ERR_TRIGGERED: adj = "TRIGGERED";break;
        case INA_ERR_TRUE: adj = "TRUE"; break;
        case INA_ERR_UNIQUE: adj = "UNIQUE"; break;
        case INA_ERR_UP: adj = "UP"; break;
        case INA_ERR_UPDATED: adj = "UPDATED"; break;
        case INA_ERR_UPGRADED: adj = "UPGRADED"; break;
        case INA_ERR_UPLOADED: adj = "UPLOADED"; break;
        case INA_ERR_USED: adj = "USED"; break;
        case INA_ERR_VALID: adj = "VALID"; break;
        case INA_ERR_WORKING: adj = "WORKING"; break;
        case INA_ERR_WRITABLE: adj = "WRITABLE"; break;
        case INA_ERR_WRONG: adj = "WRONG"; break;
        case INA_ERR_END_OF: adj = "END OF"; break;
        case INA_ERR_RESOLVED: adj = "RESOLVED"; break;
        case INA_ERR_MATCH: adj = "MATCH"; break;
        case INA_ERR_TRY_AGAIN: adj = "TRY AGAIN"; break;
        case INA_ERR_PARSED: adj = "PARSED"; break;
        case INA_ERR_CHANGED: adj = "CHANGED";
    };

    {
        INA_DISABLE_WARNING_MSVC(4204)
        const char *common[] = {noun, neg, adj};
        const char *special[] = {neg, adj, noun};
        INA_ENABLE_WARNING_MSVC(4204)

        const char **use = common;

        ina_rc_t type = rc & (0x1FFULL << INA_RC_BIT_C);

        if ((type == INA_ERR_A) || (type == INA_ERR_NOT_A) ||
            (type == INA_ERR_NO) || (type == INA_ERR_NO_SUCH) ||
            (type == INA_ERR_ENOUGH) || (type == INA_ERR_NOT_ENOUGH)) {
            use = special;
        }
        ina_str_snprintf(&__errmsg, __INA_ERROR_MSGLEN,
                "%s%s%s%s%s - 0x%" PRIx64 " - error=%u,ver=%u,rev=%u,os=%u,neg=%u,adj=%u,subject=%u,code=%u,ubits=0x%x",
                (use)[0],
                (use)[0][0]?" ":"",
                (use)[1],
                (use)[1][0]?" ":"",
                (use)[2],
                rc,
                INA_RC_EFLAG(rc),
                INA_RC_VER(rc),
                INA_RC_REV(rc),
                INA_RC_ERRNO(rc),
                INA_RC_NFLAG(rc),
                INA_RC_ADJ(rc),
                INA_RC_SUBJECT(rc),
                INA_RC_CODE(rc),
                INA_RC_UBITS(rc));
        return __errmsg;
    }
}

