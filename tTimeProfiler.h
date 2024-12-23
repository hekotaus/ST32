#pragma once

struct tTimeProfile {
    int64_t curBegin = 0;    
    int64_t curEnd = 0;    
    int64_t curDur = 0;    
    int64_t maxDur = 0;    
    int64_t minDur = 0;
    int64_t totDur = 0;
    int64_t n = 0;
    int64_t slowestTS = 0; // Timestamp for the longest duration
    bool ticked = false;

    void reset() {
        curBegin = 0;    
        curEnd = 0;    
        curDur = 0;
        maxDur = 0;
        minDur = 0;
        totDur = 0;
        n = 0;
        slowestTS = 0;
        ticked = false;
    }
};

typedef int64_t (*ProfTimCallback)();

class tTimeProfiler {
private:
	size_t ProfilesCount = 0;
	ProfTimCallback CbGetTime = nullptr;
//	std::vector<tTimeProfile> Prof;
	tTimeProfile Prof[30];

	void tick(uint32_t profId, int64_t nowTime) {
		Prof[profId].ticked = true;
		Prof[profId].curBegin = nowTime;
	}

	void tock(uint32_t profId, int64_t nowTime) {
    	if (!Prof[profId].ticked) return;
        Prof[profId].curEnd = nowTime; 
        Prof[profId].curDur = Prof[profId].curEnd - Prof[profId].curBegin; 
        Prof[profId].totDur+= Prof[profId].curDur;
        if (Prof[profId].n == 0) {
            Prof[profId].minDur = Prof[profId].curDur;
            Prof[profId].maxDur = Prof[profId].curDur;
        } else {
            if (Prof[profId].minDur > Prof[profId].curDur)
                Prof[profId].minDur = Prof[profId].curDur;
            if (Prof[profId].maxDur < Prof[profId].curDur) {
                Prof[profId].maxDur = Prof[profId].curDur;
                Prof[profId].slowestTS = nowTime;
            }
        }
        Prof[profId].n++;
        Prof[profId].ticked = false;
    }

public:
	explicit tTimeProfiler(size_t profilesCount, ProfTimCallback cbGetTime)
	: ProfilesCount(profilesCount)
	, CbGetTime(cbGetTime) {
		//Prof.resize(ProfilesCount);
	}

	void reset() { for(auto & prof : Prof) prof.reset(); }

	void reset(uint32_t profId) { Prof[profId].reset(); }

    void tick(uint32_t profId) {
    	if (profId >= ProfilesCount) return;
        int64_t nowTime = CbGetTime();
        tick(profId, nowTime);
    }

    void tock(uint32_t profId) {
    	if (profId >= ProfilesCount) return;
        int64_t nowTime = CbGetTime();
        tock(profId, nowTime);
    }

    int64_t maxDur(uint32_t profId) const {
    	if (profId >= ProfilesCount) return -1;
    	return Prof[profId].maxDur;
    }

    int64_t minDur(uint32_t profId) const {
    	if (profId >= ProfilesCount) return -1;
    	return Prof[profId].minDur;
    }

    int64_t avgDur(uint32_t profId) const {
    	if (profId >= ProfilesCount) return -1;
        return (Prof[profId].n == 0) ? 0 : Prof[profId].totDur / Prof[profId].n;
    }
};
