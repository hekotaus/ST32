#pragma once

class tTimeout {
	uint32_t Timeout = -1;
	uint32_t LastUpdate = 0;
    bool Active = true;
public:

    void Update(uint32_t timestamp) {
        Active = true;
        LastUpdate = timestamp;
    }

    bool CheckActive(uint32_t timestamp) {
        if (Active && (timestamp > (LastUpdate + Timeout)))
            Active = false;
        return Active;
    }

    bool CheckTimeout(uint32_t timestamp) {
        return !CheckActive(timestamp);
    }

    bool IsTimeout() const {
        return !Active;
    }

    bool IsActive() const {
        return Active;
    }


    void SetTimeout(uint32_t timeout) {
        Timeout = timeout;
    }    

    uint32_t GetLeftover(uint32_t timestamp) {
    	if (CheckActive(timestamp)) {
    		return (LastUpdate + Timeout) - timestamp;
    	}
    	return 0; // Exceeded
    }

    tTimeout(uint32_t timeout, uint32_t timestamp, bool timeout_state)
    : Timeout(timeout)
    {
    	if (timeout_state)
    		Active = false;
    	else
    		Update(timestamp);
    }

};
