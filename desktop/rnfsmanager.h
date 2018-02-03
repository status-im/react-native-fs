/**
 * Copyright (c) 2017-present, Status Research and Development GmbH.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#ifndef RNFSMANAGER_H
#define RNFSMANAGER_H

#include "moduleinterface.h"

#include <QVariantMap>
#include <QDateTime>

class RNFSManagerPrivate;
class RNFSManager : public QObject, public ModuleInterface {
    Q_OBJECT
    Q_INTERFACES(ModuleInterface)

    Q_DECLARE_PRIVATE(RNFSManager)

public:
    Q_INVOKABLE RNFSManager(QObject* parent = 0);
    ~RNFSManager();

    void setBridge(Bridge* bridge) override;

    QString moduleName() override;
    QList<ModuleMethod*> methodsToExport() override;
    QVariantMap constantsToExport() override;

    Q_INVOKABLE REACT_PROMISE void readDir(QString dirPath, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    Q_INVOKABLE REACT_PROMISE void exists(QString filepath, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    Q_INVOKABLE REACT_PROMISE void stat(QString filepath, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    Q_INVOKABLE REACT_PROMISE void writeFile(QString filepath, QString base64Content, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    Q_INVOKABLE REACT_PROMISE void appendFile(QString filepath, QString base64Content, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    Q_INVOKABLE REACT_PROMISE void write(QString filepath, QString base64Content, int position, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    Q_INVOKABLE REACT_PROMISE void unlink(QString filepath, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    Q_INVOKABLE REACT_PROMISE void mkdir(QString filepath, QVariantMap options, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    Q_INVOKABLE REACT_PROMISE void readFile(QString filepath, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    Q_INVOKABLE REACT_PROMISE void read(QString filepath, int length, int position, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    Q_INVOKABLE REACT_PROMISE void hash(QString filepath, QString algorithm, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    Q_INVOKABLE REACT_PROMISE void moveFile(QString filepath, QString destPath, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    Q_INVOKABLE REACT_PROMISE void copyFile(QString filepath, QString destPath, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    Q_INVOKABLE REACT_PROMISE void downloadFile(QVariantMap options, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    Q_INVOKABLE void stopDownload(int jobId);
    Q_INVOKABLE void resumeDownload(int jobId);
    Q_INVOKABLE REACT_PROMISE void isResumable(int jobId, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    Q_INVOKABLE REACT_PROMISE void uploadFiles(QVariantMap options, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    Q_INVOKABLE void stopUpload(int jobId);
    Q_INVOKABLE REACT_PROMISE void pathForBundle(QString bundleNamed, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    Q_INVOKABLE REACT_PROMISE void pathForGroup(QString groupId, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    Q_INVOKABLE REACT_PROMISE void getFSInfo(const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);
    Q_INVOKABLE REACT_PROMISE void touch(QString filepath, QDateTime mtime, QDateTime ctime, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject);

private:
    QScopedPointer<RNFSManagerPrivate> d_ptr;

    bool copyRecursively(const QString& src, const QString& dst);
    bool removeRecursively(const QString& path);
};

#endif // RNFSMANAGER_H
