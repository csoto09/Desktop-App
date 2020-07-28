#ifndef TOOLTIPCONTROLLER_H
#define TOOLTIPCONTROLLER_H

#include <QObject>
#include "serverratingstooltip.h"
#include "tooltiptypes.h"
#include "itooltip.h"

class TooltipController : public QObject
{
    Q_OBJECT
public:
    explicit TooltipController(QObject *parent = nullptr);

    void hideAllTooltips();
    void showTooltipInteractive(TooltipId id, int x, int y, int delay);
    void showTooltipBasic(TooltipInfo info);
    void showTooltipDescriptive(TooltipInfo info);
    void hideTooltip(TooltipId type);

    void clearServerRatings();

signals:
    void sendServerRatingUp();
    void sendServerRatingDown();

private slots:
    void onServerRatingsTooltipRateUpClicked();
    void onServerRatingsTooltipRateDownClicked();

private:
    ServerRatingsTooltip *serverRatingsTooltip_;
    ServerRatingState serverRatingState_;

    QMap<TooltipId, ITooltip*> tooltips_;

};

#endif // TOOLTIPCONTROLLER_H