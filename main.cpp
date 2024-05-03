

#include <QApplication>
#include <QStyle>
#include <QStyleFactory>

#include "mainwindow.h"


int main(int argc, char *argv[])
{
#if !defined(__GNUC__)
#error "Wrong compiler or platform!"
#endif

#if CHAR_BIT != 8
#error "unsupported char size"
#endif

#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
#error "system is not little endian!"
#endif

  char str[512]={""};

  union
  {
    char four[4];
    int one;
  } byte_order_test_var;

  /* avoid surprises! */
  if((sizeof(char)      != 1) ||
     (sizeof(short)     != 2) ||
     (sizeof(int)       != 4) ||
     (sizeof(long long) != 8) ||
     (sizeof(float)     != 4) ||
     (sizeof(double)    != 8))
  {
    fprintf(stderr, "Wrong compiler or platform!\n");
    return EXIT_FAILURE;
  }

#if defined(__LP64__)
  if(sizeof(long) != 8)
  {
    fprintf(stderr, "Wrong compiler or platform!\n");
    return EXIT_FAILURE;
  }
#else
  if(sizeof(long) != 4)
  {
    fprintf(stderr, "Wrong compiler or platform!\n");
    return EXIT_FAILURE;
  }
#endif

  /* check endianness! */
  byte_order_test_var.one = 0x03020100;
  if((byte_order_test_var.four[0] != 0) ||
     (byte_order_test_var.four[1] != 1) ||
     (byte_order_test_var.four[2] != 2) ||
     (byte_order_test_var.four[3] != 3))
  {
    fprintf(stderr, "Wrong compiler or platform!\n");
    return EXIT_FAILURE;
  }

  QApplication app(argc, argv);

#if QT_VERSION >= 0x050000
  qApp->setStyle(QStyleFactory::create("Fusion"));
#endif
  qApp->setStyleSheet("QLabel, QMessageBox { messagebox-text-interaction-flags: 5; }");

  UI_Mainwindow *MainWindow = new UI_Mainwindow;
  if(MainWindow == NULL)
  {
    snprintf(str, 512, "Malloc error.\nFile: %s  line: %i", __FILE__, __LINE__);

    fprintf(stderr, "%s\n", str);

    QMessageBox::critical(NULL, "Error", str);

    return EXIT_FAILURE;
  }

  int ret = app.exec();

  delete MainWindow;

  return ret;
}






