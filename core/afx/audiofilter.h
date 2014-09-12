#ifndef AUDIOFILTER_H
#define AUDIOFILTER_H

#include "engine/filter.h"
#include "engine/frame.h"



class AudioFilter : public Filter
{
public:
	AudioFilter( QString id, QString name ) : Filter( id, name ) {}
	virtual ~AudioFilter() {}
	virtual bool process( Frame*, Profile* ) { return true; }
	virtual bool process( Frame* /*src*/, Frame* /*dst*/, Profile* ) { return true; }
};

#endif //AUDIOFILTER_H
