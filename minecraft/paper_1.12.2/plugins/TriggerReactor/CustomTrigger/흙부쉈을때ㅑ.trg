IF $worldname == "world"
block = event.getBlock().getTypeId()
IF block == 2 || block == 3
event.setDropItems(false);
#CMDOP "give $playername minecraft:paper 1 0 "
ENDIF
ENDIF