set confirm off
define reload
  file build/SDLog_Lite.elf
  load
  monitor reset halt
end
