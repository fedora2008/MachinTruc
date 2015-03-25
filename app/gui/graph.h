#ifndef GRAPH_H
#define GRAPH_H

#include <QGraphicsScene>
#include <QPainter>

#include "timeline/clipviewitem.h"
#include "engine/thumbnailer.h"



class GraphEffectItem;



class Graph : public QGraphicsScene
{
	Q_OBJECT
public:
	Graph( bool audio = false );
	
	void setCurrentClip( ClipViewItem *c );
	ClipViewItem *getClip() { return currentClip; }
	void effectMoved( GraphEffectItem *it, qreal y );
	void effectReleased( GraphEffectItem *it );
	
public slots:
	void viewSizeChanged( const QSize &size );
	void itemSelected( GraphEffectItem *it );
	void effectRightClick( GraphEffectItem *it );
	
protected:
	void dragEnterEvent( QGraphicsSceneDragDropEvent *event );
	void dragMoveEvent( QGraphicsSceneDragDropEvent *event );
	void dragLeaveEvent( QGraphicsSceneDragDropEvent *event );
	void dropEvent( QGraphicsSceneDragDropEvent *event );

private slots:
	void updateLength();
	void rebuildGraph();
	
private:
	bool isAudio;
	int viewHeight;
	ClipViewItem *currentClip;
	GraphEffectItem *selectedItem;
	QList<GraphEffectItem*> dragList;
	
signals:
	void filterSelected( Clip*, int index );
	void filterDeleted( Clip*, QSharedPointer<Filter> );
	void filterAdded( ClipViewItem*, QString, int );
	void updateFrame();
};

#endif // GRAPH_H