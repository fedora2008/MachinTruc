#include "projectprofiledialog.h"


typedef struct AudioPreset_ {
	int samplerate;
	int layout;
} AudioPreset;

typedef struct VideoPreset_ {
	int width;
	int height;
	QString ratio;
	int framerate; /*fpsPresets index*/
	int scanning;
} VideoPreset;

static const int nfpspresets = 8;
static const double fpsPresets[ nfpspresets ] = {
	24000. / 1001.,
	24,
	25,
	30000. / 1001.,
	30,
	50,
	60000. / 1001.,
	60
};

static const int nvpresets = 20;
static const VideoPreset vPresets[ nvpresets ] = {
	{ 1920, 1080, "16:9", 0, 0 },
	{ 1920, 1080, "16:9", 1, 0 },
	{ 1920, 1080, "16:9", 2, 0 },
	{ 1920, 1080, "16:9", 3, 0 },
	{ 1920, 1080, "16:9", 4, 0 },
	{ 1920, 1080, "16:9", 5, 0 },
	{ 1920, 1080, "16:9", 6, 0 },
	{ 1920, 1080, "16:9", 7, 0 },
	
	{ 1280, 720, "16:9", 0, 0 },
	{ 1280, 720, "16:9", 1, 0 },
	{ 1280, 720, "16:9", 2, 0 },
	{ 1280, 720, "16:9", 3, 0 },
	{ 1280, 720, "16:9", 4, 0 },
	{ 1280, 720, "16:9", 5, 0 },
	{ 1280, 720, "16:9", 6, 0 },
	{ 1280, 720, "16:9", 7, 0 },
	
	{ 720, 576, "16:9", 2, 0 },
	{ 720, 576, "4:3", 2, 0 },
	{ 720, 480, "16:9", 3, 0 },
	{ 720, 480, "4:3", 3, 0 }
};



ProjectProfileDialog::ProjectProfileDialog( QWidget *parent, Profile p ) : QDialog( parent )
{
	setupUi( this );

	audioPresetLab->setEnabled( false );
	audioPresetCombo->setEnabled( false );
	layoutLab->setEnabled( false );
	layoutCombo->setEnabled( false );
	samplerateLab->setEnabled( false );
	samplerateSpinBox->setEnabled( false );

	videoPresetCombo->addItem( tr("Custom") );
	for ( int i = 0; i < nvpresets; ++i ) {
		videoPresetCombo->addItem( QString("%1x%2 - %3 - %4fps")
			.arg(vPresets[i].width)
			.arg(vPresets[i].height)
			.arg(vPresets[i].ratio)
			.arg( QString::number( fpsPresets[ vPresets[i].framerate ], 'f', 2 )  ) );
	}

	widthSpinBox->setRange( 1, 1920 );
	heightSpinBox->setRange( 1, 1080 );
	
	ratioCombo->addItem( "16:9" );
	ratioCombo->addItem( "4:3" );
	ratioCombo->addItem( "Size" );
	
	for ( int i = 0; i < nfpspresets; ++i )
		framerateCombo->addItem( QString::number( fpsPresets[i], 'f', 2 ) );
	
	scanningCombo->addItem( "Progressive" );
	scanningCombo->addItem( "Top Field First" );
	scanningCombo->addItem( "Bottom Field First" );
	
	widthSpinBox->setValue( p.getVideoWidth() );
	heightSpinBox->setValue( p.getVideoHeight() );

	double ar = p.getVideoWidth() * p.getVideoSAR() / p.getVideoHeight();
	if ( qAbs( ar - 16./9. ) < 1e-3 )
		ratioCombo->setCurrentIndex( 0 );
	else if ( qAbs( ar - 4./3. ) < 1e-3 )
		ratioCombo->setCurrentIndex( 1 );
	else
		ratioCombo->setCurrentIndex( 2 );
	
	for ( int i = 0; i < nfpspresets; ++i ) {
		if ( qAbs( p.getVideoFrameRate() - fpsPresets[i] ) < 1e-3 ) {
			framerateCombo->setCurrentIndex( i );
			break;
		}
	}
	
	scanningCombo->setEnabled( false );
	
	connect( videoPresetCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(presetChanged(int)) );
}



void ProjectProfileDialog::presetChanged( int index )
{
	if ( index == 0 )
		return;
	
	widthSpinBox->setValue( vPresets[index - 1].width );
	heightSpinBox->setValue( vPresets[index - 1].height );
	
	if ( vPresets[index - 1].ratio == "16:9" )
		ratioCombo->setCurrentIndex( 0 );
	else if ( vPresets[index - 1].ratio == "4:3" )
		ratioCombo->setCurrentIndex( 1 );
	
	framerateCombo->setCurrentIndex( vPresets[index - 1].framerate );
}
