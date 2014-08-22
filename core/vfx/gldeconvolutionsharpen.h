#ifndef GLDECONVOLUTIONSHARPEN_H
#define GLDECONVOLUTIONSHARPEN_H

#include "vfx/glfilter.h"



class GLDeconvolutionSharpen : public GLFilter
{
public:
	GLDeconvolutionSharpen( QString id, QString name );
	~GLDeconvolutionSharpen();

	bool process( const QList<Effect*> &el, Frame *src, Profile *p );

	QList<Effect*> getMovitEffects();
	QString getDescriptor();
	
private:
	Parameter *R;
	Parameter *circleRadius, *gaussianRadius, *correlation, *noise;
};

#endif //GLDECONVOLUTIONSHARPEN_H
