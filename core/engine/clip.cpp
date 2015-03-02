#include "engine/clip.h"
#include "engine/util.h"



Clip::Clip( Source *src, double posInTrackPTS, double strt, double len )
	: source( src ),
	posInTrack( posInTrackPTS ),
	clipStart( strt ),
	clipLength( len ),
	frameDuration( MICROSECOND / 25.0 ),
	in( NULL ),
	transition( NULL )
{
}



Clip::~Clip()
{
	if ( in )
		in->setUsed( false );
	if ( transition )
		delete transition;
}



void Clip::setPosition( double p )
{
	posInTrack = p;
	
	for ( int i = 0; i< videoFilters.count(); ++i )
		videoFilters.at( i )->setPosition( posInTrack );
	for ( int i = 0; i< audioFilters.count(); ++i )
		audioFilters.at( i )->setPosition( posInTrack );
	if ( transition )
		transition->setPosition( posInTrack );
}



void Clip::setLength( double len )
{
	clipLength = len;
	
	for ( int i = 0; i< videoFilters.count(); ++i )
		videoFilters.at( i )->setLength( length() );
	for ( int i = 0; i< audioFilters.count(); ++i )
		audioFilters.at( i )->setLength( length() );
}



double Clip::length()
{
	return nearestPTS( clipLength, frameDuration );
}



void Clip::setFrameDuration( double d )
{
	frameDuration = d;
	for ( int i = 0; i< videoFilters.count(); ++i )
		videoFilters.at( i )->setLength( length() );
	for ( int i = 0; i< audioFilters.count(); ++i )
		audioFilters.at( i )->setLength( length() );
	if ( transition )
		transition->setFrameDuration( frameDuration );
}



void Clip::setInput( InputBase *i )
{
	if ( in && i != in )
		in->setUsed( false );
	in = i;
	if ( in )
		in->setUsed( true );
}



void Clip::setTransition( double len )
{
	if ( !transition )
		transition = new Transition( posInTrack, len );
	transition->setPosition( posInTrack );
	transition->setLength( len );
	transition->setFrameDuration( frameDuration );
}



void Clip::removeTransition()
{
	if ( transition )
		delete transition;
	transition = NULL;
}
