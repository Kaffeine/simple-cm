/*
    Copyright (C) 2014 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef SIMPLECM_PROTOCOL_H
#define SIMPLECM_PROTOCOL_H

#include "simplecm_export.h"

#include <TelepathyQt/BaseProtocol>

class SimpleConnection;

class SIMPLECM_EXPORT SimpleProtocol : public Tp::BaseProtocol
{
    Q_OBJECT
    Q_DISABLE_COPY(SimpleProtocol)

public:
    SimpleProtocol(const QDBusConnection &dbusConnection, const QString &name);
    virtual ~SimpleProtocol();

    QString connectionManagerName() const;
    void setConnectionManagerName(const QString &newName);

public slots:
    void sendMessage(QString sender, QString message);
    void setContactList(QStringList list);
    void setContactPresence(const QString &identifier, const QString &presence);

signals:
    void messageReceived(QString sender, QString message);

    void newMessageToBeSent(QString sender, QString message);
    void contactsListChanged(QStringList list);
    void vCardListChanged(QStringList list);

    void contactPresenceChanged(const QString &identifier, const QString &presence);

protected:
    virtual void connectionCreatedEvent(SimpleConnection *newConnection);

private:
    Tp::BaseConnectionPtr createConnection(const QVariantMap &parameters, Tp::DBusError *error);
    QString identifyAccount(const QVariantMap &parameters, Tp::DBusError *error);
    QString normalizeContact(const QString &contactId, Tp::DBusError *error);

    // Proto.I.Addressing
    QString normalizeVCardAddress(const QString &vCardField, const QString vCardAddress,
            Tp::DBusError *error);
    QString normalizeContactUri(const QString &uri, Tp::DBusError *error);

    Tp::BaseProtocolAddressingInterfacePtr addrIface;
    Tp::BaseProtocolAvatarsInterfacePtr avatarsIface;
    Tp::BaseProtocolPresenceInterfacePtr presenceIface;

    QString m_connectionManagerName;
};

inline QString SimpleProtocol::connectionManagerName() const
{
    return m_connectionManagerName;
}

#endif // SIMPLECM_PROTOCOL_H
