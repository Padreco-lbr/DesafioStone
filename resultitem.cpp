#include "resultitem.h"
#include "player.h"
#include <QtWidgets>

ResultItem::ResultItem(QString title, QUrl previewUrl, QString artist, QUrl albumPictureUrl,
                       QString albumName, QWidget *parent, Player *player) :
    QWidget(parent)
{
    m_player = player;

    m_title = title;
    m_previewUrl = previewUrl;
    m_artist = artist;
    m_albumPictureUrl = albumPictureUrl;
    m_albumName = albumName;

    QHBoxLayout *vLayout = new QHBoxLayout;

    QLabel *txtLine = new QLabel(title, this);

    QToolButton *m_playButton = new QToolButton(this);
    m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    m_playButton->setToolTip("Play!");

    QToolButton *m_addButton = new QToolButton(this);
    m_addButton->setIcon(style()->standardIcon(QStyle::SP_DialogApplyButton));
    m_addButton->setToolTip("Add to Playlist");

    vLayout->addWidget(m_addButton);
    vLayout->addWidget(m_playButton);
    vLayout->addWidget(txtLine);

    setLayout(vLayout);

    connect(m_playButton, SIGNAL(clicked(bool)), this, SLOT(playThisPressed()));
    connect(m_addButton, SIGNAL(clicked(bool)), this, SLOT(addToPlaylistPressed()));
    connect(this, SIGNAL(playThis(QUrl)), m_player, SLOT(play(QUrl)));
}


ResultItem::~ResultItem(){
    QTextStream out(stdout);
    out << "ResultItem " << m_title << " has been destroyed" << endl;
}


//public slots
void ResultItem::playThisPressed(){
    emit playThis(m_previewUrl);
}


void ResultItem::addToPlaylistPressed(){
    m_player->getStatusBarInstance()->showMessage("added!");
}
