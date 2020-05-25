#MESSAGE $worldname
#MESSAGE $worldname == "world"
#MESSAGE $worldname == world
block = event.getBlockPlaced().getTypeId()
IF block == 2 || block == 3
#MESSAGE "흙을 설치하려면 교환권을 사용해야해요!"
event.setCancelled(true)
ENDIF
