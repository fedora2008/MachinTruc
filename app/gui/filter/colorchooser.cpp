#include <QColorDialog>

#include "colorchooser.h"



ColorChooser::ColorChooser( bool rgba, QWidget *parent, Parameter *p, bool keyframeable ) : ParameterWidget( parent, p )
{
	Q_UNUSED( keyframeable );
	hasAlpha = rgba;
	
	QBoxLayout *b1 = new QBoxLayout( QBoxLayout::LeftToRight );
	b1->setContentsMargins( 0, 0, 0, 0 );
	widgets.append( label = new QLabel( p->name ) );
	b1->addWidget( label );
	
	QBoxLayout *b2 = new QBoxLayout( QBoxLayout::LeftToRight );
	b2->setContentsMargins( 0, 0, 0, 0 );
	widgets.append( btn = new QPushButton( "..." ) );
	b2->addWidget( btn );
	
	box = new QBoxLayout( QBoxLayout::TopToBottom );
	box->setContentsMargins( 0, 0, 0, 0 );
	box->addLayout( b1 );
	box->addLayout( b2 );

	connect( btn, SIGNAL(clicked()), this, SLOT(showDialog()) );
}



void ColorChooser::showDialog()
{
	QColorDialog dlg;
	//dlg.setParent( this );
	if ( hasAlpha )
		dlg.setOption( QColorDialog::ShowAlphaChannel );
	dlg.setOption( QColorDialog::NoButtons );
	dlg.setCurrentColor( param->value.value<QColor>() );
	connect( &dlg, SIGNAL(currentColorChanged(const QColor&)), this, SLOT(colorChanged(const QColor&)) );
	dlg.exec();
}



void ColorChooser::colorChanged( const QColor &col )
{
	emit valueChanged( param, col );
}



void ColorChooser::animValueChanged( double val )
{
	Q_UNUSED( val );
}
