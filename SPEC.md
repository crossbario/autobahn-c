http://www.digip.org/jansson/
http://kgabis.github.io/parson/


ANSI C (C89) WebSocket/WAMP client library with WSS support
runs on FreeRTOS/CyaSSL
Apache 2.0 license


Jansson 
http://www.digip.org/jansson/

Parson
https://github.com/kgabis/parson


http://elk.informatik.fh-augsburg.de/hhweb/labor/arm/stm32-discovery/index.html


http://electronicdesign.com/embedded/practical-advice-running-uclinux-cortex-m3m4
https://github.com/EmcraftSystems

    /**
     * Besides a API for raw WebSocket, AutobahnC exposes a WAMP API for talking
     * with WAMP-compatible servers.
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

    typedef enum ab_result_t {
        AB_WAMP_CONNE
        AB_WAMP_SESSION_CLOSED = 10,
        AB_SQUEUE_CLOSED = 1,
        AB_SQUEUE_EMPTY = 2,
        AB_SQUEUE_FULL = 3,
    }
	

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
	

	...

    int ab_transmit (const char* data, int length);

    int ab_receive (const char* data, int length);

	
	void ab_squeue_connect (const char* hostname,
                            int port,
                            ab_squeue_onconnect onconnect,
                            ab_sqeue_onclose onclose);
	
	typedef void (*ab_squeue_onconnect) (ab_squeue_t* squeue);
	
	typedef void (*ab_sqeue_onclose) (ab_squeue_t* squeue, int reason, const char* desc)
	
	ab_result_t ab_squeue_put (ab_squeue_t* squeue, ab_squeue_cargo cargo);

    /* Get next cargo from socket queue. When successful, returns 0.
     * When a cargo could not be retrieved, the return value indicates
     * the reason. This function never blocks.
     */
    ab_result_t ab_squeue_get (ab_squeue_t* squeue, ab_squeue_cargo* cargo);

    typedef struct ab_squeue_cargo {
       int length;
       int capacity;
       void* data;
    }
