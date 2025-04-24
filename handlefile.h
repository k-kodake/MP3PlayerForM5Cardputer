#include <SD.h>
String files[2000] = {};
String files2[2000] = {};
int no_of_files = 0;
int selectNum;
extern void listFolder(void);

void printDirectory(File dir) {
  while (true) {
    //フォルダー内の次のファイル
    File entry = dir.openNextFile();
    if (!entry) {
      break;  //オープンする内容が無ければループを抜ける
    }
    //ファイル（フォルダー）名の表示
    if (entry.isDirectory()) {
      //フォルダーならフォルダーの中を表示
      printDirectory(entry);
    } else {
      //ファイルサイズの表示
      files[no_of_files] = entry.path();
      files2[no_of_files++] = entry.name();
    }
    entry.close();  //終わったら呼び出し先に戻る
  }
}
size_t selfile() {
  M5Cardputer.Lcd.fillScreen(BLACK);
  M5Cardputer.Lcd.setCursor(0, 0);
  M5Cardputer.Lcd.println("*** File List ***");

  selectNum = 0;
  listFolder();
  bool exitMenu = false;

  while (!exitMenu) {
    M5Cardputer.update();
    if (M5Cardputer.Keyboard.isKeyPressed(';')) {
      if (selectNum > 0) {
        selectNum--;
        listFolder();
      }
    }
    if (M5Cardputer.Keyboard.isKeyPressed('.')) {
      if (selectNum < no_of_files - 1) {
        selectNum++;
        listFolder();
      }
    }
    if (M5Cardputer.Keyboard.isKeyPressed(' ')) {
      exitMenu = true;
    }
    delay(100);
  }
  return selectNum;
}

void listFolder() {
  M5Cardputer.Lcd.fillScreen(BLACK);
  M5Cardputer.Lcd.setCursor(0, 0);
  M5Cardputer.Lcd.println("*** File List ***");

  M5Cardputer.Lcd.setCursor(0, 30);
  for (int i = selectNum; i < no_of_files; i++) {
    if (i == selectNum) {
      M5Cardputer.Lcd.println("> " + files2[i]);
    } else {
      M5Cardputer.Lcd.println("  " + files2[i]);
    }
  }
}
