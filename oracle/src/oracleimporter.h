#ifndef ORACLEIMPORTER_H
#define ORACLEIMPORTER_H

#include <carddatabase.h>
#include <QHttp>

class QProgressDialog;
class QBuffer;

class SetToDownload {
private:
	QString shortName, longName, url;
public:
	const QString &getShortName() const { return shortName; }
	const QString &getLongName() const { return longName; }
	const QString &getUrl() const { return url; }
	SetToDownload(const QString &_shortName, const QString &_longName, const QString &_url)
		: shortName(_shortName), longName(_longName), url(_url) { }
};

class OracleImporter : public CardDatabase {
	Q_OBJECT
private:
	QList<SetToDownload> setsToDownload;
	QMap<QString, QStringList> colorOverride;
	QMap<QString, int> tableRowOverride;
	int setIndex;
	int reqId;
	QBuffer *buffer;
	QHttp *http;
	QProgressDialog *progressDialog;
private slots:
	void httpRequestFinished(int requestId, bool error);
	void readResponseHeader(const QHttpResponseHeader &responseHeader);
public:
	OracleImporter();
	void importOracleFile(CardSet *set);
	void downloadNextFile();
};

#endif