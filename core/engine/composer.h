#ifndef COMPOSER_H
#define COMPOSER_H

#include "movitchain.h"
#include "vfx/glmix.h"
#include "vfx/gloverlay.h"
#include "filtercollection.h"

#include <QGLWidget>
#include <QThread>

#include "engine/sampler.h"



class Composer : public QThread
{
	Q_OBJECT
public:
	Composer( Sampler *samp );
	~Composer();

	void play( bool b );
	void seeking();
	void runOneShot();
	void updateFrame( Frame *dst );

public slots:
	void setSharedContext( QGLWidget *shared );
	void discardFrame();

private:
	void run();
	
	int process( Frame **frame );
	Frame* getNextFrame( Frame *dst, int &track );
	bool renderVideoFrame( Frame *dst );
	void movitRender( Frame *dst, bool update = false );
	bool renderAudioFrame( Frame *dst, int nSamples );

	bool running;
	bool oneShot;
	int skipFrame;

	GLuint mask_texture;
	
	GLuint videoPBO;
	QGLWidget *hiddenContext;
	GLResource gl;

	MovitChain movitChain;
	ResourcePool *movitPool;
	QStringList movitDescriptor;

	Sampler *sampler;
	double audioSampleDelta;

signals:
	void newFrame( Frame* );
	void paused( bool );

};

#endif // COMPOSER_H
