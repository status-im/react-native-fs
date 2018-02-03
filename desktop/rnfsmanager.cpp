/**
 * Copyright (c) 2017-present, Status Research and Development GmbH.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include "rnfsmanager.h"
#include "bridge.h"
#include "eventdispatcher.h"

#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QVariant>
#include <QByteArray>

namespace {
struct RegisterQMLMetaType {
    RegisterQMLMetaType() {
        qRegisterMetaType<RNFSManager*>();
    }
} registerMetaType;
} // namespace

class RNFSManagerPrivate {
public:
    Bridge* bridge = nullptr;
};

RNFSManager::RNFSManager(QObject* parent) : QObject(parent), d_ptr(new RNFSManagerPrivate) {}

RNFSManager::~RNFSManager() {}

void RNFSManager::setBridge(Bridge* bridge) {
    Q_D(RNFSManager);
    d->bridge = bridge;
}

QString RNFSManager::moduleName() {
    return "RNFSManager";
}

QList<ModuleMethod*> RNFSManager::methodsToExport() {
    return QList<ModuleMethod*>{};
}

QVariantMap RNFSManager::constantsToExport() {
    return QVariantMap();
}

void RNFSManager::readDir(QString dirPath, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {

}

void RNFSManager::exists(QString filepath, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {

}

void RNFSManager::stat(QString filepath, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {

}

void RNFSManager::writeFile(QString filepath, QString base64Content, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {

}

void RNFSManager::appendFile(QString filepath, QString base64Content, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {

}

void RNFSManager::write(QString filepath, QString base64Content, int position, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {

}

void RNFSManager::unlink(QString filepath, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {

}

void RNFSManager::mkdir(QString filepath, QVariantMap options, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {

}

void RNFSManager::readFile(QString filepath, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {
    Q_D(RNFSManager);
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        reject(d->bridge, QVariantList());
        return;
    }
    QByteArray fileData = file.readAll().toBase64();
    resolve(d->bridge, QVariantList{{QVariant(fileData)}});
}

void RNFSManager::read(QString filepath, int length, int position, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {

}

void RNFSManager::hash(QString filepath, QString algorithm, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {

}

void RNFSManager::moveFile(QString filepath, QString destPath, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {
    Q_D(RNFSManager);

    if (copyRecursively(filepath, destPath) &&
        removeRecursively(filepath)) {
        resolve(d->bridge, QVariantList());
    } else {
        reject(d->bridge, QVariantList());
    }
}

void RNFSManager::copyFile(QString filepath, QString destPath, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {

}

void RNFSManager::downloadFile(QVariantMap options, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {

}

void RNFSManager::stopDownload(int jobId) {

}

void RNFSManager::resumeDownload(int jobId) {

}

void RNFSManager::isResumable(int jobId, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {

}

void RNFSManager::uploadFiles(QVariantMap options, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {

}

void RNFSManager::stopUpload(int jobId) {

}

void RNFSManager::pathForBundle(QString bundleNamed, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {

}

void RNFSManager::pathForGroup(QString groupId, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {

}

void RNFSManager::getFSInfo(const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {

}

void RNFSManager::touch(QString filepath, QDateTime mtime, QDateTime ctime, const ModuleInterface::ListArgumentBlock& resolve, const ModuleInterface::ListArgumentBlock& reject) {

}

bool RNFSManager::copyRecursively(const QString& src, const QString& dst) {
    QFileInfo filePathFileInfo(src);
    if (filePathFileInfo.isDir()) {
        QDir dstDir(dst);
        if (!dstDir.isRoot()) {
            dstDir.cdUp();
            if (!dstDir.mkdir(QFileInfo(dst).fileName()))
                return false;
        }
        QDir srcDir(src);
        QStringList itemNames = srcDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::System | QDir::Hidden );
        foreach (const QString &itemName, itemNames) {
            if (!copyRecursively(src + QDir::separator() + itemName, dst + QDir::separator() + itemName))
                return false;
        }
    } else {
        return QFile::copy(src, dst);
    }
    return true;
}

bool RNFSManager::removeRecursively(const QString& path) {
    QFileInfo filePathFileInfo(path);
    if (filePathFileInfo.isDir()) {
        QDir dir(path);
        return dir.removeRecursively();
    } else {
        return QFile::remove(path);
    }
}



