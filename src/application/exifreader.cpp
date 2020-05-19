#include "exifreader.h"
#include <QDebug>
ExifReader::ExifReader(QObject* parent) : QObject(parent) {}

bool ExifReader::openFile(const QFile& file) {
  QString fileName = file.fileName();

  // Read the JPEG file into a buffer
  FILE* fp = fopen(fileName.toStdString().c_str(), "rb");
  if (!fp) {
    return false;
  }
  fseek(fp, 0, SEEK_END);
  unsigned long fsize = ftell(fp);
  rewind(fp);
  unsigned char* buf = new unsigned char[fsize];
  if (fread(buf, 1, fsize, fp) != fsize) {
    delete[] buf;
    return false;
  }
  fclose(fp);

  // Parse EXIF

  int code = m_exif.parseFrom(buf, fsize);
  delete[] buf;
  if (code) {
    return false;
  }
  return true;
}

bool ExifReader::haveExif() const {
  return m_exifReadSuccessful;
}

QDateTime ExifReader::originalDateTime() {
  return str2dt(m_exif.DateTimeOriginal);
}

QDateTime ExifReader::imageDateTime() {
  return str2dt(m_exif.DateTime);
}

QDateTime ExifReader::digitizedDateTime() {
  return str2dt(m_exif.DateTimeDigitized);
}

QDateTime ExifReader::str2dt(const std::string& s) {
  QString str = QString::fromStdString(s);
  return QDateTime::fromString(str, "yyyy:MM:dd hh:mm:ss");
}
