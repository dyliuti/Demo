#include "listdelegate.h"
#include "listmodel.h"
#include <QComboBox>
#include <QFont>
#include <QPainter>
#include <QSvgRenderer>

static QMap<ListData::Type, QString> s_typeImg {
    { ListData::Type::PPT, ":/com/img/list/ppt.svg" },
    { ListData::Type::EXCEL, ":/com/img/list/excel.svg" },
    { ListData::Type::WORD, ":/com/img/list/word.svg" },
    { ListData::Type::PDF, ":/com/img/list/pdf.svg" },
    { ListData::Type::EXPANSION_BOARD, ":/com/img/list/expansionBoard.svg" },
    { ListData::Type::MAIN_BOARD, ":/com/img/list/mainBoard.svg" },
};
static int s_itemHeight = 40;
static int s_typeImgHeight = 20;
static int s_selectImgHeight = 12;

QSize ListDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return QSize(option.rect.width(), s_itemHeight);
}

void ListDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    painter->save();

    const auto& rect = option.rect;
    // check
    bool bSelect = option.state & QStyle::State_Selected;
    if (bSelect) {
        QRect rectImage(rect.topLeft().x() + 8, rect.topLeft().y() + (s_itemHeight - s_selectImgHeight) / 2, s_selectImgHeight, s_selectImgHeight);
        QSvgRenderer svg(QString(":/com/img/list/select.svg"));
        svg.render(painter, rectImage);
    }

    // type img
    QRect typeRect(rect.topLeft().x() + 28, rect.topLeft().y() + (s_itemHeight - s_typeImgHeight) / 2, s_typeImgHeight, s_typeImgHeight);
    ListData::Type type = (ListData::Type)index.data(ListModel::TypeRole).toInt();
    QString imgPath = s_typeImg[type];
    QSvgRenderer svg2(imgPath);
    svg2.render(painter, typeRect);

    // showName
    painter->setPen(QPen(QColor(bSelect ? "#FFFFFF" : "#C3C3C3")));
    QFont font;
    font.setPointSize(12);
    painter->setFont(font);
    QString showName = index.data(ListModel::NameRole).toString();
    painter->drawText(rect.adjusted(56, 0, 0, 0), showName, Qt::AlignLeft | Qt::AlignVCenter);

    painter->restore();
}

QSize SpliteLineDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return QSize(option.rect.width(), 9);
}

void SpliteLineDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    painter->save();
    painter->setPen(QPen(QColor("#424242")));
    auto midH = option.rect.y() + option.rect.height() / 2;
    painter->drawLine(0, midH, option.rect.width(), midH);
    painter->restore();
}
