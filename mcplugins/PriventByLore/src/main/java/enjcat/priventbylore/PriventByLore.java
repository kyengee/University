package enjcat.priventbylore;

import org.bukkit.Bukkit;
import org.bukkit.event.EventHandler;
import org.bukkit.event.Listener;
import org.bukkit.event.block.BlockDamageEvent;
import org.bukkit.event.block.BlockPlaceEvent;
import org.bukkit.event.enchantment.PrepareItemEnchantEvent;
import org.bukkit.event.inventory.InventoryAction;
import org.bukkit.event.inventory.InventoryClickEvent;
import org.bukkit.event.inventory.PrepareAnvilEvent;
import org.bukkit.event.player.PlayerDropItemEvent;
import org.bukkit.event.player.PlayerItemBreakEvent;
import org.bukkit.event.player.PlayerItemConsumeEvent;
import org.bukkit.event.player.PlayerItemDamageEvent;
import org.bukkit.plugin.java.JavaPlugin;

import java.util.List;

public final class PriventByLore extends JavaPlugin implements Listener {

    @Override
    public void onEnable() {
        // Plugin startup logic
        //set up config
        getConfig().options().copyDefaults();
        saveDefaultConfig();

        getServer().getPluginManager().registerEvents(this, this);
    }

    @EventHandler
    public void onPlayerDropItem(PlayerDropItemEvent e){
        String Lore = getConfig().getString("lore");
        List<String> ItemLores = e.getItemDrop().getItemStack().getItemMeta().getLore();
        if(ItemLores != null)
            for(String LoreNow : ItemLores){
                if(LoreNow.equals(Lore))
                    e.setCancelled(true);
            }
    }
    @EventHandler
    public void onPlayerItemConsume(PlayerItemConsumeEvent e){
        String Lore = getConfig().getString("lore");
        List<String> ItemLores = e.getItem().getItemMeta().getLore();
        if(ItemLores != null)
            for(String LoreNow : ItemLores){
                if(LoreNow.equals(Lore))
                    e.setCancelled(true);
            }
    }
    @EventHandler
    public void onInventoryClick(InventoryClickEvent e){
        String Lore = getConfig().getString("lore");
        if(e.getAction() == InventoryAction.MOVE_TO_OTHER_INVENTORY ||
                e.getAction() == InventoryAction.PICKUP_SOME ||
                e.getAction() == InventoryAction.PICKUP_ONE ||
                e.getAction() == InventoryAction.PICKUP_HALF ||
                e.getAction() == InventoryAction.PICKUP_ALL) {
            List<String> ItemLores = e.getCurrentItem().getItemMeta().getLore();
            if (ItemLores != null)
                for (String LoreNow : ItemLores) {
                    if (LoreNow.equals(Lore))
                        e.setCancelled(true);
                }
        }
    }
    @EventHandler
    public void onPrepareItemEnchant(PrepareItemEnchantEvent e){
        String Lore = getConfig().getString("lore");
        List<String> ItemLores = e.getItem().getItemMeta().getLore();
        if(ItemLores != null)
            for(String LoreNow : ItemLores){
                if(LoreNow.equals(Lore))
                    e.setCancelled(true);
            }
    }
    @EventHandler
    public void onBlockPlace(BlockPlaceEvent e){
        String Lore = getConfig().getString("lore");
        List<String> ItemLores = e.getItemInHand().getItemMeta().getLore();
        if(ItemLores != null)
            for(String LoreNow : ItemLores){
                if(LoreNow.equals(Lore))
                    e.setCancelled(true);
            }
    }
    @EventHandler
    public void onPlayerItemDamage(PlayerItemDamageEvent e){
        String Lore = getConfig().getString("lore");
        List<String> ItemLores = e.getItem().getItemMeta().getLore();
        if(ItemLores != null)
            for(String LoreNow : ItemLores){
                if(LoreNow.equals(Lore))
                    e.setCancelled(true);
            }
    }
}
