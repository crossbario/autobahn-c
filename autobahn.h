/**
 * AutobahnC. Copyright (c) 2013 Tavendo GmbH. All rights reserved.
 *
 * Besides a API for raw WebSocket, AutobahnC exposes a WAMP API for
 * talking to WAMP-compatible servers:
 */

/**
 * Open a new WAMP session to a server.
 */
ab_result_t ab_wamp_connect (json_t* sessionconfig,
                             void* cbdata,
                             ab_wamp_onconnect onconnect,
                             ab_wamp_onclose onclose);

typdef void (*ab_wamp_onconnect) (void* cbdata,
                                  ab_wamp_session_t* session,
                                  json_t* sessioninfo);

typdef void (*ab_wamp_onclose) (void* cbdata,
                                ab_wamp_session_t* session,
                                int reason,
                                const char* desc);


/**
 * Call a remote procedure.
 */
ab_result_t ab_call (ab_wamp_session_t* session,
                     const char* endpoint,
                     json_t* args,
                     void* cbdata,
                     ab_onsuccess onsuccess,
                     ab_onerror onerror);

typedef void (*ab_onsuccess) (void* cbdata,
                              json_t* result);

typedef void (*ab_onerror) (void* cbdata,
                            const char* error,
                            const char* desc,
                            json_t* details);


/**
 * Subscribe to topics.
 */
ab_result_t ab_subscribe (ab_wamp_session_t* session,
                          const char* topic,
                          void* cbdata,
                          ab_onevent onevent);

typedef void (*ab_onevent) (void* cbdata,
                            const char* topic,
                            json_t* event);


/**
 * Publish to topics.
 */
ab_result_t ab_publish (ab_wamp_session_t* session,
                        const char* topic,
                        json_t* event);


/**
 * Process WAMP protocol data coming in from the network via the
 * underlying socket queue. This function never blocks.
 */
ab_result_t ab_wamp_loop_once (ab_wamp_session_t* session);
