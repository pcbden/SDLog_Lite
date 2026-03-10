define reload
  delete
  directory
  symbol-file
  symbol-file build/SDLog_Lite.elf
  load
  monitor reset halt
end
define reset
  monitor reset halt
end
