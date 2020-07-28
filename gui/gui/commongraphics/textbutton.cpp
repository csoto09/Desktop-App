#include "textbutton.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QCursor>
#include "graphicresources/fontmanager.h"
#include "commongraphics.h"
#include "dpiscalemanager.h"

namespace CommonGraphics {

TextButton::TextButton(QString text, const FontDescr &fd, QColor color, bool bSetClickable, ScalableGraphicsObject *parent, int addWidth) : ClickableGraphicsObject(parent),
    fontDescr_(fd), addWidth_(addWidth)
{
    curTextOpacity_ = OPACITY_UNHOVER_TEXT;
    unhoverOpacity_ = OPACITY_UNHOVER_TEXT;

    textAlignment_ = Qt::AlignLeft | Qt::AlignVCenter;

    text_ = text;
    fontDescr_ = fd;
    color_ = color;

    connect(&textOpacityAnimation_, SIGNAL(valueChanged(QVariant)), SLOT(onTextHoverOpacityChanged(QVariant)));

    // Direct constructor call to ClickableGraphicsObject::setCursor() crashes due to "pure virtual function call" for some reason only in this class...
    setClickable(bSetClickable);

    recalcBoundingRect();
}

QRectF TextButton::boundingRect() const
{
    return QRectF(0, 0, width_, height_ + MARGIN_HEIGHT*G_SCALE );
}

void TextButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal initialOpacity = painter->opacity();

    painter->setOpacity(curTextOpacity_ * initialOpacity);
    QFont *font = FontManager::instance().getFont(fontDescr_);
    painter->setFont(*font);
    painter->setPen(color_);

    painter->drawText(boundingRect(), textAlignment_ , text_);
}

double TextButton::getOpacity()
{
    return curTextOpacity_;
}

void TextButton::quickSetOpacity(double opacity)
{
    curTextOpacity_ = opacity;
    update();
}

void TextButton::quickHide()
{
    setClickable(false);
    curTextOpacity_ = OPACITY_HIDDEN;
}

void TextButton::animateShow(int animationSpeed)
{
    setClickable(true);
    startAnAnimation<double>(textOpacityAnimation_, curTextOpacity_, unhoverOpacity_, animationSpeed);
}

void TextButton::animateHide(int animationSpeed)
{
    setClickable(false);

    startAnAnimation<double>(textOpacityAnimation_, curTextOpacity_, OPACITY_HIDDEN, animationSpeed);
}

int TextButton::getWidth()
{
    QFont *font = FontManager::instance().getFont(fontDescr_);
    return textWidth(text_,*font);
}

void TextButton::setText(QString text)
{
    text_ = text;
    recalcBoundingRect();
    update();
}

QString TextButton::text()
{
    return text_;
}

void TextButton::setCurrentOpacity(double opacity)
{
    curTextOpacity_ = opacity;
    update();
}

void TextButton::setUnhoverOpacity(double unhoverOpacity)
{
    unhoverOpacity_ = unhoverOpacity;
}

void TextButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (clickable_)
    {
        if (event->button() == Qt::LeftButton)
        {
            if (pressed_)
            {
                pressed_ = false;

                if (contains(event->pos()))
                {
                    setCursor(Qt::ArrowCursor);

                    emit clicked();
                }
            }
        }
    }
    else
    {
        event->ignore();
        return;
    }
}

void TextButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);

    if (hoverable_)
    {
        startAnAnimation<double>(textOpacityAnimation_, curTextOpacity_, OPACITY_FULL, ANIMATION_SPEED_FAST);
        if (clickable_)
        {
            setCursor(Qt::PointingHandCursor);
        }
        emit hoverEnter();
    }
}

void TextButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);

    startAnAnimation<double>(textOpacityAnimation_, curTextOpacity_, unhoverOpacity_, ANIMATION_SPEED_FAST);
    setCursor(Qt::ArrowCursor);

    emit hoverLeave();
}

void TextButton::onTextHoverOpacityChanged(const QVariant &value)
{
    curTextOpacity_ = value.toDouble();
    update();
}

void TextButton::recalcBoundingRect()
{
    QFont *font = FontManager::instance().getFont(fontDescr_);
    QFontMetrics fm(*font);

    prepareGeometryChange();
    width_ = fm.boundingRect(text_).width() + addWidth_*G_SCALE;
    height_ = fm.height();
}

void TextButton::setTextAlignment(int alignment)
{
    textAlignment_ = alignment;
    update();
}

}