#ifndef EXIFREADER_H
#define EXIFREADER_H

#include <QDateTime>
#include <QFile>
#include <QObject>
#include "exif.h"

class ExifReader : public QObject {
  Q_OBJECT
 public:
  explicit ExifReader(QObject* parent = nullptr);

  //! Open a file and access its exif information. This function was based on
  //! demo code from EasyExif libtary by Mayank Lahiri
  //!
  bool openFile(const QFile& file);

  bool haveExif() const;

  QDateTime originalDateTime();
  QDateTime imageDateTime();
  QDateTime digitizedDateTime();

 private:
  easyexif::EXIFInfo m_exif;
  bool m_exifReadSuccessful = false;

  QDateTime str2dt(const std::string& s);
};

#endif  // EXIFREADER_H
