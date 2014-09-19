#ifndef TRACKVIEWITEM_H
#define TRACKVIEWITEM_H

#include <QGraphicsRectItem>



class TrackViewItem : public QGraphicsRectItem
{
public:
	TrackViewItem();

	void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
	
protected:
	void mousePressEvent( QGraphicsSceneMouseEvent * event );
};

#endif // TRACKVIEWITEM_H
