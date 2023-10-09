#define DECODE_SONY
#define DECODE_SAMSUNG
#include <IRremote.hpp>

//#define DEBUG

namespace
{
  const unsigned int RecvPin    = 5;
  const unsigned int SendPin    = 6;
  const unsigned int SendLedPin = 13;

  enum class Cycle
  {
    RecvLoopEntry = 0,
    RecvLoop      = 1,
    SendLoopEntry = 2,
    SendLoop      = 3,
    SendLoopExit  = 4
  };
  Cycle CurrentCycle = Cycle::RecvLoopEntry;

  IRData RecvData;

  unsigned int SendTimerMs            = 0;
  const unsigned int LoopDelayMs      = 100;
  const unsigned int SendDelayMs      = 10000;
  const unsigned int SendPostDelayMs  = 1000;
}

void setup()
{
  log_setup();
}

void loop()
{
  switch (CurrentCycle)
  {
    case Cycle::RecvLoopEntry:
      recv_loop_entry();
      break;

    case Cycle::RecvLoop:
      recv_loop();
      break;

    case Cycle::SendLoopEntry:
      send_loop_entry();
      break;

    case Cycle::SendLoop:
      send_loop();
      break;

    case Cycle::SendLoopExit:
      send_loop_exit();
      break;
  }

  log_loop();

  delay(LoopDelayMs);
}

void recv_loop_entry()
{
  IrReceiver.begin(RecvPin, false, 0);
  CurrentCycle = Cycle::RecvLoop;
}

void recv_loop()
{
  if (IrReceiver.decode())
  {
    if (IrReceiver.decodedIRData.decodedRawData != 0 &&
        IrReceiver.decodedIRData.protocol != UNKNOWN)
    {
      RecvData = IrReceiver.decodedIRData;
      IrReceiver.stop();
      CurrentCycle = Cycle::SendLoopEntry;
    }
    else
    {
      IrReceiver.resume();
    }
  }
}

void send_loop_entry()
{
  IrSender.begin(SendPin, true, SendLedPin);
  CurrentCycle = Cycle::SendLoop;
}

void send_loop()
{
  SendTimerMs += LoopDelayMs;
  if (SendTimerMs > SendDelayMs)
  {
    const unsigned char repeats = 4;
    switch (RecvData.protocol)
    {
      case SONY:
        IrSender.sendSony(RecvData.address, RecvData.command, repeats);
        break;

      case SAMSUNG:
        IrSender.sendSamsung(RecvData.address, RecvData.command, repeats);
        break;
    }

    SendTimerMs   = 0;
    CurrentCycle  = Cycle::SendLoopExit;
  }
}

void send_loop_exit()
{
  SendTimerMs += LoopDelayMs;
  if (SendTimerMs > SendPostDelayMs)
  {
    IrReceiver.restartAfterSend();
    IrReceiver.resume();

    SendTimerMs  = 0;
    CurrentCycle = Cycle::RecvLoopEntry;
  }
}

void log_setup()
{
#ifdef DEBUG
  Serial.begin(115200);
  Serial.print("Ready to receive IR signals of protocols: ");
  printActiveIRProtocols(&Serial);
#endif // DEBUG
}

void log_loop()
{
#ifdef DEBUG
  switch (CurrentCycle)
  {
    case Cycle::RecvLoopEntry:
      Serial.println("=============================");
      Serial.println("CurrentCycle: RecvLoopEntry");
      Serial.println("=============================");
      break;

    case Cycle::RecvLoop:
      Serial.println("=============================");
      Serial.println("CurrentCycle: RecvLoop");
      Serial.println("=============================");
      break;

    case Cycle::SendLoopEntry:
      Serial.println("=============================");
      Serial.println("CurrentCycle: SendLoopEntry");
      IrReceiver.printIRResultShort(&Serial);
      Serial.println("=============================");
      break;

    case Cycle::SendLoop:
      Serial.println("=============================");
      Serial.println("CurrentCycle: SendLoop");
      Serial.println("=============================");
      break;

    case Cycle::SendLoopExit:
      Serial.println("=============================");
      Serial.println("CurrentCycle: SendLoopExit");
      Serial.println("=============================");
      break;
  }
#endif // DEBUG
}
