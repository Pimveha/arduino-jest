#include <LedControl.h>
#include <SD.h>


// LED display pins
const int DIN_PIN = 11;
const int CLK_PIN = 13;
const int CS_PIN = 10;
const int NUM_MODULES = 4;

// SD card pin
const int SD_CS_PIN = 4;

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, NUM_MODULES);

const int DISPLAY_COLS = NUM_MODULES * 8;

// font
struct Glyph {
  char c;
  uint8_t width;
  uint8_t col[5];
};
const Glyph FONT[] PROGMEM = {
  {' ', 3, {0x00,0x00,0x00,0x00,0x00}},
  {'!', 1, {0x5F,0x00,0x00,0x00,0x00}},
  {'"', 3, {0x07,0x00,0x07,0x00,0x00}},
  {'#', 5, {0x14,0x7F,0x14,0x7F,0x14}},
  {'$', 5, {0x24,0x2A,0x7F,0x2A,0x12}},
  {'%', 5, {0x23,0x13,0x08,0x64,0x62}},
  {'&', 5, {0x36,0x49,0x56,0x20,0x50}},
  {'\'', 1, {0x07,0x00,0x00,0x00,0x00}},
  {'(', 3, {0x1C,0x22,0x41,0x00,0x00}},
  {')', 3, {0x41,0x22,0x1C,0x00,0x00}},
  {'*', 5, {0x2A,0x1C,0x7F,0x1C,0x2A}},
  {'+', 5, {0x08,0x08,0x3E,0x08,0x08}},
  {',', 2, {0xA0,0x60,0x00,0x00,0x00}},
  {'-', 4, {0x08,0x08,0x08,0x08,0x00}},
  {'—', 5, {0x08,0x08,0x08,0x08,0x08}},
  {'.', 2, {0x60,0x60,0x00,0x00,0x00}},
  {'/', 5, {0x20,0x10,0x08,0x04,0x02}},
  {'0', 5, {0x3E,0x51,0x49,0x45,0x3E}},
  {'1', 3, {0x42,0x7F,0x40,0x00,0x00}},
  {'2', 5, {0x42,0x61,0x51,0x49,0x46}},
  {'3', 5, {0x21,0x41,0x45,0x4B,0x31}},
  {'4', 5, {0x18,0x14,0x12,0x7F,0x10}},
  {'5', 5, {0x27,0x45,0x45,0x45,0x39}},
  {'6', 5, {0x3C,0x4A,0x49,0x49,0x30}},
  {'7', 5, {0x01,0x71,0x09,0x05,0x03}},
  {'8', 5, {0x36,0x49,0x49,0x49,0x36}},
  {'9', 5, {0x06,0x49,0x49,0x52,0x3C}},
  {':', 2, {0x36,0x36,0x00,0x00,0x00}},
  {';', 2, {0xA6,0x66,0x00,0x00,0x00}},
  {'<', 4, {0x08,0x14,0x22,0x41,0x00}},
  {'=', 4, {0x14,0x14,0x14,0x14,0x00}},
  {'>', 4, {0x41,0x22,0x14,0x08,0x00}},
  {'?', 5, {0x02,0x01,0x51,0x09,0x06}},
  {'@', 5, {0x3E,0x41,0x5D,0x59,0x4E}},
  {'A', 5, {0x7E,0x09,0x09,0x09,0x7E}},
  {'B', 5, {0x7F,0x49,0x49,0x49,0x36}},
  {'C', 5, {0x3E,0x41,0x41,0x41,0x22}},
  {'D', 5, {0x7F,0x41,0x41,0x22,0x1C}},
  {'E', 5, {0x7F,0x49,0x49,0x49,0x41}},
  {'F', 5, {0x7F,0x09,0x09,0x09,0x01}},
  {'G', 5, {0x3E,0x41,0x49,0x49,0x7A}},
  {'H', 5, {0x7F,0x08,0x08,0x08,0x7F}},
  {'I', 3, {0x41,0x7F,0x41,0x00,0x00}},
  {'J', 5, {0x20,0x40,0x41,0x3F,0x01}},
  {'K', 5, {0x7F,0x08,0x14,0x22,0x41}},
  {'L', 5, {0x7F,0x40,0x40,0x40,0x40}},
  {'M', 5, {0x7F,0x02,0x0C,0x02,0x7F}},
  {'N', 5, {0x7F,0x04,0x08,0x10,0x7F}},
  {'O', 5, {0x3E,0x41,0x41,0x41,0x3E}},
  {'P', 5, {0x7F,0x09,0x09,0x09,0x06}},
  {'Q', 5, {0x3E,0x41,0x51,0x21,0x5E}},
  {'R', 5, {0x7F,0x09,0x19,0x29,0x46}},
  {'S', 5, {0x46,0x49,0x49,0x49,0x31}},
  {'T', 5, {0x01,0x01,0x7F,0x01,0x01}},
  {'U', 5, {0x3F,0x40,0x40,0x40,0x3F}},
  {'V', 5, {0x1F,0x20,0x40,0x20,0x1F}},
  {'W', 5, {0x3F,0x40,0x30,0x40,0x3F}},
  {'X', 5, {0x63,0x14,0x08,0x14,0x63}},
  {'Y', 5, {0x07,0x08,0x70,0x08,0x07}},
  {'Z', 5, {0x61,0x51,0x49,0x45,0x43}},
  {'[', 3, {0x7F,0x41,0x41,0x00,0x00}},
  {'\\', 5, {0x02,0x04,0x08,0x10,0x20}},
  {']', 3, {0x41,0x41,0x7F,0x00,0x00}},
  {'^', 5, {0x04,0x02,0x01,0x02,0x04}},
  {'_', 4, {0x40,0x40,0x40,0x40,0x00}},
  {'a', 4, {0x20,0x54,0x54,0x78,0x00}},
  {'b', 4, {0x7F,0x48,0x44,0x38,0x00}},
  {'c', 4, {0x38,0x44,0x44,0x28,0x00}},
  {'d', 4, {0x38,0x44,0x48,0x7F,0x00}},
  {'e', 4, {0x38,0x54,0x54,0x18,0x00}},
  {'f', 4, {0x08,0x7E,0x09,0x02,0x00}},
  {'g', 4, {0x18,0xA4,0xA4,0x7C,0x00}},
  {'h', 4, {0x7F,0x08,0x04,0x78,0x00}},
  {'i', 1, {0x7D,0x00,0x00,0x00,0x00}},
  {'j', 3, {0x40,0x80,0x7A,0x00,0x00}},
  {'k', 4, {0x7F,0x10,0x28,0x44,0x00}},
  {'l', 1, {0x7F,0x00,0x00,0x00,0x00}},
  {'m', 5, {0x7C,0x04,0x78,0x04,0x78}},
  {'n', 4, {0x7C,0x08,0x04,0x78,0x00}},
  {'o', 4, {0x38,0x44,0x44,0x38,0x00}},
  {'p', 4, {0xFC,0x24,0x24,0x18,0x00}},
  {'q', 4, {0x18,0x24,0x24,0xFC,0x00}},
  {'r', 4, {0x7C,0x08,0x04,0x08,0x00}},
  {'s', 4, {0x48,0x54,0x54,0x24,0x00}},
  {'t', 3, {0x04,0x3F,0x44,0x00,0x00}},
  {'u', 4, {0x3C,0x40,0x40,0x7C,0x00}},
  {'v', 4, {0x1C,0x20,0x40,0x3C,0x00}},
  {'w', 5, {0x3C,0x40,0x30,0x40,0x3C}},
  // {'x', 4, {0x44,0x28,0x10,0x6C,0x00}}, alternative x, looks better imo
  {'x', 4, {0x44,0x28,0x28,0x44,0x00}},
  {'y', 4, {0x1C,0xA0,0xA0,0x7C,0x00}},
  {'z', 4, {0x44,0x64,0x54,0x4C,0x00}},
};


// buffer parameters
const int SLIDE_BUF_SIZE = 256;
char textBuffer[SLIDE_BUF_SIZE];
int bufLen = 0; // number of valid chars in textBuffer

File textFile;
bool fileOpened = false;
unsigned long lastReadTime = 0;
const unsigned long READ_INTERVAL = 10000; // 10 seconds between reads (keeps previous behavior)

// // uppercase conversion
// const Glyph& findGlyph(char c) {
//   if (c >= 'a' && c <= 'z') {
//     c = c - 'a' + 'A';
//   }
  
//   for (int i = 0; i < sizeof(FONT)/sizeof(FONT[0]); i++) {
//     if (pgm_read_byte(&FONT[i].c) == c) {
//       return FONT[i];
//     }
//   }
//   return FONT[0]; // space fallback
// }

const Glyph& findGlyph(char c) {
  for (int i = 0; i < sizeof(FONT)/sizeof(FONT[0]); i++) {
    if (pgm_read_byte(&FONT[i].c) == c) {
      return FONT[i];
    }
  }
  return FONT[0]; // return space if character is not found
}

int messagePixelLength(const char* msg) {
  int len = 0;
  for (const char* p = msg; *p; ++p) {
    const Glyph& g = findGlyph(*p);
    len += pgm_read_byte(&g.width) + 1;
  }
  return len;
}

// drawFrame unchanged, draws any null-terminated C string that lives in RAM
void drawFrame(const char* msg, int offset) {
  uint8_t rows[NUM_MODULES][8];
  for (int m = 0; m < NUM_MODULES; m++)
    for (int r = 0; r < 8; r++)
      rows[m][r] = 0;

  int xCursor = offset;
  for (const char* p = msg; *p; ++p) {
    const Glyph& g = findGlyph(*p);
    uint8_t width = pgm_read_byte(&g.width);
    for (int col = 0; col < width; col++) {
      int x = xCursor + col;
      if (x >= 0 && x < DISPLAY_COLS) {
        int module = x / 8;
        int bitPos = x % 8;
        uint8_t colBits = pgm_read_byte(&g.col[col]);
        for (int row = 0; row < 8; row++) {
          if (colBits & (1 << (7 - row))) {
            rows[module][row] |= (1 << bitPos);
          }
        }
      }
    }
    xCursor += width + 1;
  }

  for (int m = 0; m < NUM_MODULES; m++)
    for (int r = 0; r < 8; r++)
      lc.setRow(m, r, rows[m][r]);
}

// append characters from the open textFile into the end of textBuffer
void appendFromFile() {
  if (!fileOpened) return;

  // reopen file if at EOF -> infinite loop :)
  if (!textFile.available()) {
    textFile.close();
    // file name must be uppercase and no more than 5 chars
    textFile = SD.open("IJ.TXT", FILE_READ); // file name on SD card
    if (!textFile) {
      // can't reopen: show error in buffer
      bufLen = 0;
      const char *err = "FILE ERROR ";
      strncpy(textBuffer, err, SLIDE_BUF_SIZE - 1);
      bufLen = min((int)strlen(err), SLIDE_BUF_SIZE - 1);
      textBuffer[bufLen] = '\0';
      return;
    }
  }

  while (textFile.available() && bufLen < SLIDE_BUF_SIZE - 1) {
    char c = textFile.read();
    // skip weird control chars and turn newlines into spaces
    if (c < 32 && c != '\n' && c != '\r' && c != '\t') continue;
    if (c == '\n' || c == '\r') c = ' ';
    textBuffer[bufLen++] = c;
    // if buffer is mostly full, break at a space to avoid cutting words
    if (c == ' ' && bufLen > SLIDE_BUF_SIZE * 0.8) break;
  }
  textBuffer[bufLen] = '\0';
}

// remove the first character from buffer (slide left), keep buffer null-terminated
void removeFirstCharFromBuffer() {
  if (bufLen <= 0) return;
  memmove(textBuffer, textBuffer + 1, bufLen - 1);
  bufLen--;
  textBuffer[bufLen] = '\0';
}

void scrollText() {
  static int offset = DISPLAY_COLS;
  static unsigned long last = 0;
  const unsigned long interval = 40; // ms per shift
  if (millis() - last < interval) return;
  last = millis();

  if (bufLen == 0) {
    appendFromFile();
    if (bufLen == 0) {
      const char* p = "NO FILE ";
      drawFrame(p, offset);
      return;
    }
  }

  // draw current content
  drawFrame(textBuffer, offset);
  offset--;

  char first = textBuffer[0];
  const Glyph &gfirst = findGlyph(first);
  int firstWidth = pgm_read_byte(&gfirst.width) + 1; // include the 1-column spacing

  if (offset <= -firstWidth) {
    // remove the character and shift buffer left
    removeFirstCharFromBuffer();
    offset += firstWidth;
  }

  // refill buffer when it gets low
  if (bufLen < 32) {
    // but rate-limit actual SD reads so we don't hammer the card
    if (millis() - lastReadTime > READ_INTERVAL) {
      appendFromFile();
      lastReadTime = millis();
    }
  }
}

void setup() {
  Serial.begin(9600);
  
  // initialize LED display
  for (int i = 0; i < NUM_MODULES; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 0);
    lc.clearDisplay(i);
  }
  
  // initialize SD card
  if (!SD.begin(SD_CS_PIN)) {
    bufLen = 0;
    const char *err = "SD ERROR ";
    strncpy(textBuffer, err, SLIDE_BUF_SIZE - 1);
    bufLen = min((int)strlen(err), SLIDE_BUF_SIZE - 1);
    textBuffer[bufLen] = '\0';
    return;
  }
  
  // open file
  // file name must be uppercase and no more than 5 chars
  // file name on SD card
  if (SD.exists("IJ.TXT")) {
    textFile = SD.open("IJ.TXT", FILE_READ);
    if (textFile) {
      fileOpened = true;
      bufLen = 0;
      textBuffer[0] = '\0';
      appendFromFile(); // initial fill
    } else {
      bufLen = 0;
      const char *err = "OPEN ERROR ";
      strncpy(textBuffer, err, SLIDE_BUF_SIZE - 1);
      bufLen = min((int)strlen(err), SLIDE_BUF_SIZE - 1);
      textBuffer[bufLen] = '\0';
    }
  } else {
    bufLen = 0;
    const char *err = "NO FILE ";
    strncpy(textBuffer, err, SLIDE_BUF_SIZE - 1);
    bufLen = min((int)strlen(err), SLIDE_BUF_SIZE - 1);
    textBuffer[bufLen] = '\0';
  }
}

void loop() {
  scrollText();
}
