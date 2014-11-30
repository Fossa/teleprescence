/*
* Copyright (C) 2013 Mamadou DIOP
* Copyright (C) 2013 Doubango Telecom <http://www.doubango.org>
* License: GPLv3
* This file is part of the open source SIP TelePresence system <https://code.google.com/p/telepresence/>
*/
#ifndef OPENTELEPRESENCE_PATTERNVIDEO_HANGOUT_H
#define OPENTELEPRESENCE_PATTERNVIDEO_HANGOUT_H

#include "opentelepresence/patterns/OTPatternVideo.h"
#include "opentelepresence/OTBridge.h"

class OTPatternVideoHangout : public OTPatternVideo
{
protected:
	OTPatternVideoHangout(OTObjectWrapper<OTBridgeInfo*> oBridgeInfo);
public:
	virtual ~OTPatternVideoHangout();
	virtual OT_INLINE const char* getObjectId() { return "OTPatternVideoHangout"; }

	// Override from OTPatternVideo
	virtual OTObjectWrapper<OTFrameVideo *> mix(std::map<uint64_t, OTObjectWrapper<OTProxyPluginConsumerVideo*> > *pOTConsumers, void** pDstBuffer, uint32_t *pDstBufferSize);

	static OTObjectWrapper<OTPatternVideoHangout*> New(OTObjectWrapper<OTBridgeInfo*> oBridgeInfo);

	//***
	bool setSpeaker( string spkr );

private:
	struct AVFrame *m_pFrameMix;
	OTRatio_t m_parSpeaker;
	OTRatio_t m_parListener;

	//***
	std::vector< string > consumersVector;
	string consumersSpeaker;
	size_t consumersCount;
	//Casablanca stefan;

	// Used for set speaker
	OTObjectWrapper<OTProxyPluginConsumerVideo*> > _consumers;
};

#endif /* OPENTELEPRESENCE_PATTERNVIDEO_HANGOUT_H */
