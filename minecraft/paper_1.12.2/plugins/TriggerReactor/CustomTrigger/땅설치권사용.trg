IF $worldname == "world"
IF event.getAction().name() == "LEFT_CLICK_BLOCK"
IF event.getPlayer().getItemInHand().getItemMeta() != null
IF event.getPlayer().getItemInHand().getItemMeta().getDisplayName() != null
IF event.getPlayer().getItemInHand().getItemMeta().getDisplayName().contains("흙 설치권")
#MESSAGE "흙을 설치합니다"
event.getClickedBlock().setTypeId(2)
event.getPlayer().getItemInHand().setAmount(event.getPlayer().getItemInHand().getAmount()-1)
ENDIF
ENDIF
ENDIF
ENDIF
ENDIF