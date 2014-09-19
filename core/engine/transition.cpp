#include "util.h"

#include "filtercollection.h"
#include "transition.h"



Transition::Transition( double posInTrackPTS, double len )
	: posInTrack( posInTrackPTS ),
	transitionLength( len )
{
	videoFilter = FilterCollection::getGlobalInstance()->videoTransitions.first().create().staticCast<GLFilter>();
	videoFilter->setPosition( posInTrack );
	videoFilter->setLength( transitionLength );
	
	audioFilter = FilterCollection::getGlobalInstance()->audioTransitions.first().create().staticCast<AudioFilter>();
	audioFilter->setPosition( posInTrack );
	audioFilter->setLength( transitionLength );
}



void Transition::setVideoFilter( GLFilter *f )
{
}



void Transition::setAudioFilter( AudioFilter *f )
{
}



void Transition::setPosition( double p )
{
	posInTrack = p;
	videoFilter->setPosition( posInTrack );
	audioFilter->setPosition( posInTrack );
}



double Transition::length()
{
	return nearestPTS( transitionLength, frameDuration );
}



void Transition::setLength( double len )
{
	transitionLength = len;
	videoFilter->setLength( transitionLength );
	audioFilter->setLength( transitionLength );
}