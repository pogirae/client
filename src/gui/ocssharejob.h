/*
 * Copyright (C) by Roeland Jago Douma <roeland@famdouma.nl>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#ifndef OCSSHAREJOB_H
#define OCSSHAREJOB_H

#include "ocsjob.h"
#include <QVector>
#include <QList>
#include <QPair>

namespace OCC {

/**
 * @brief The OcsShareJob class
 * @ingroup gui
 *
 * Handle talking to the OCS Share API. 
 * For creation, deletion and modification of shares.
 */
class OcsShareJob : public OcsJob {
    Q_OBJECT
public:

    /**
     * Support sharetypes
     */
    enum ShareType : int {
        Link = 3
    };

    /**
     * Possible permissions
     */
    enum Permission : int {
        Read = 1,
        Update = 2,
        Create = 4,
        Delete = 8,
        Share = 16,
        All = 31
    };

    /**
     * Constructor for new shares or listing of shares
     */
    explicit OcsShareJob(AccountPtr account, QObject *parent = 0);

    /**
     * Get all the shares
     *
     * @param path Path to request shares for (default all shares)
     */
    void getShares(const QString& path = "");

    /**
     * Delete the current Share
     */
    void deleteShare(const QString &shareId);

    /**
     * Set the expiration date of a share
     *
     * @param date The expire date, if this date is invalid the expire date
     * will be removed
     */
    void setExpireDate(const QString &shareId, const QDate& date);

    /**
     * Set the password of a share
     *
     * @param password The password of the share, if the password is empty the
     * share will be removed
     */
    void setPassword(const QString &shareId, const QString& password);

    /**
     * Void set the share to be public upload
     * 
     * @param publicUpload Set or remove public upload
     */
    void setPublicUpload(const QString &shareId, bool publicUpload);

    /**
     * Create a new share
     *
     * @param path The path of the file/folder to share
     * @param shareType The type of share (user/group/link/federated)
     * @param password Optionally a password for the share
     * @param date Optionally an expire date for the share
     */
    void createShare(const QString& path, ShareType shareType, const QString& password = "", const QDate& date = QDate());

signals:
    /**
     * Result of the OCS request
     * The value parameter is only set if this was a put request.
     * e.g. if we set the password to 'foo' the QVariant will hold a QString with 'foo'.
     * This is needed so we can update the share objects properly
     *
     * @param reply The reply
     * @param value To what did we set a varialble (if we set any).
     */
    void shareJobFinished(QVariantMap reply, QVariant value);

private slots:
    void jobDone(QVariantMap reply);

private:
    QVariant _value;
};

}

#endif // OCSSHAREJOB_H
