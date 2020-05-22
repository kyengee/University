package enjcat.priventbylore;

import org.bukkit.Bukkit;
import org.bukkit.command.Command;
import org.bukkit.command.CommandExecutor;
import org.bukkit.command.CommandSender;
import org.bukkit.entity.Entity;
import org.bukkit.entity.Player;
import org.bukkit.event.Event;
import org.bukkit.event.EventHandler;
import org.bukkit.event.Listener;
import org.bukkit.event.block.Action;
import org.bukkit.event.block.BlockDamageEvent;
import org.bukkit.event.block.BlockPlaceEvent;
import org.bukkit.event.enchantment.PrepareItemEnchantEvent;
import org.bukkit.event.entity.ProjectileLaunchEvent;
import org.bukkit.event.inventory.InventoryAction;
import org.bukkit.event.inventory.InventoryClickEvent;
import org.bukkit.event.inventory.PrepareAnvilEvent;
import org.bukkit.event.player.*;
import org.bukkit.plugin.java.JavaPlugin;

import java.util.List;


public final class PriventByLore extends JavaPlugin implements Listener{

    static boolean onoff = true;

    @Override
    public void onEnable() {
        // Plugin startup logic
        //set up config
        getConfig().options().copyDefaults();
        saveDefaultConfig();

        getServer().getPluginManager().registerEvents(this, this);
        getCommand("itemPBL").setExecutor(new command());
    }


    @EventHandler
    public void onPlayerDropItem(PlayerDropItemEvent e){
        if(!e.getPlayer().isOp() && onoff) {
            String all = getConfig().getString("prevent_all");
            String option = getConfig().getString("p_DropItem");
            List<String> ItemLores = e.getItemDrop().getItemStack().getItemMeta().getLore();
            if (ItemLores != null)
                for (String LoreNow : ItemLores) {
                    if (LoreNow.contains(all) || LoreNow.contains(option))
                        e.setCancelled(true);
                }
        }
    }
    @EventHandler
    public void onPlayerItemConsume(PlayerItemConsumeEvent e){
        if(!e.getPlayer().isOp() && onoff) {
            String all = getConfig().getString("prevent_all");
            String option = getConfig().getString("p_Consume");
            List<String> ItemLores = e.getItem().getItemMeta().getLore();
            if (ItemLores != null)
                for (String LoreNow : ItemLores) {
                    if (LoreNow.contains(all) || LoreNow.contains(option))
                        e.setCancelled(true);
                }
        }
    }
    @EventHandler
    public void onInventoryClick(InventoryClickEvent e){
        if(!e.getWhoClicked().isOp() && onoff) {
            String all = getConfig().getString("prevent_all");
            String option = getConfig().getString("p_PickupInInventory");
            if (e.getAction() == InventoryAction.MOVE_TO_OTHER_INVENTORY ||
                    e.getAction() == InventoryAction.PICKUP_SOME ||
                    e.getAction() == InventoryAction.PICKUP_ONE ||
                    e.getAction() == InventoryAction.PICKUP_HALF ||
                    e.getAction() == InventoryAction.PICKUP_ALL) {
                List<String> ItemLores = e.getCurrentItem().getItemMeta().getLore();
                int i =0;
                if (ItemLores != null)
                    for (String LoreNow : ItemLores) {
                        if (LoreNow.contains(all) || LoreNow.contains(option))
                            e.setCancelled(true);
                    }
            }
        }
    }
    @EventHandler
    public void onPrepareItemEnchant(PrepareItemEnchantEvent e){
        if(!e.getEnchanter().isOp() && onoff) {
            String all = getConfig().getString("prevent_all");
            String option = getConfig().getString("p_Enchant");
            List<String> ItemLores = e.getItem().getItemMeta().getLore();
            if (ItemLores != null)
                for (String LoreNow : ItemLores) {
                    if (LoreNow.contains(all) || LoreNow.contains(option))
                        e.setCancelled(true);
                }
        }
    }
    @EventHandler
    public void onBlockPlace(BlockPlaceEvent e){
        if(!e.getPlayer().isOp() && onoff) {
            String all = getConfig().getString("prevent_all");
            String option = getConfig().getString("p_place");
            List<String> ItemLores = e.getItemInHand().getItemMeta().getLore();
            if (ItemLores != null)
                for (String LoreNow : ItemLores) {
                    if (LoreNow.contains(all) || LoreNow.contains(option))
                        e.setCancelled(true);
                }
        }
    }
    @EventHandler
    public void onPlayerItemDamage(PlayerItemDamageEvent e){
        if(!e.getPlayer().isOp() && onoff) {
            String all = getConfig().getString("prevent_all");
            String option = getConfig().getString("p_ItemDamage");
            List<String> ItemLores = e.getItem().getItemMeta().getLore();
            if (ItemLores != null)
                for (String LoreNow : ItemLores) {
                    if (LoreNow.contains(all) || LoreNow.contains(option))
                        e.setCancelled(true);
                }
        }
    }
    @EventHandler
    public void onPlayerInteractEntity(PlayerInteractEntityEvent e){
        if(!e.getPlayer().isOp() && onoff) {
            String all = getConfig().getString("prevent_all");
            String option = getConfig().getString("p_ItemFrame");
            if (e.getRightClicked().getEntityId() == 174) {
                List<String> ItemLores = e.getPlayer().getItemInHand().getItemMeta().getLore();
                if (ItemLores != null)
                    for (String LoreNow : ItemLores) {
                        if (LoreNow.contains(all) || LoreNow.contains(option))
                            e.setCancelled(true);
                    }
            }
        }
    }

    /*@EventHandler
    public void onProjectileLaunch(ProjectileLaunchEvent e){
        String all = getConfig().getString("prevent_all");
        String option = getConfig().getString("p_Projectile");
        if(e.getEntity().getShooter() instanceof Player) {
            Player p = (Player) e.getEntity().getShooter();
            p.sendMessage("플레이어가 쐈다.");
            List<String> ItemLores = p.getItemInHand().getItemMeta().getLore();
            if (ItemLores != null)
                for (String LoreNow : ItemLores) {
                    if (LoreNow.equals(all) || LoreNow.equals(option))
                        e.setCancelled(true);
                }
        }

    }*/



    @EventHandler
    public void onPlayerRightClick(PlayerInteractEvent e){
        if(!e.getPlayer().isOp() && onoff) {
            String all = getConfig().getString("prevent_all");
            String option = getConfig().getString("p_RightClick");
            if (e.getAction() == Action.RIGHT_CLICK_AIR
                    || e.getAction() == Action.RIGHT_CLICK_BLOCK) {
                List<String> ItemLores = e.getPlayer().getItemInHand().getItemMeta().getLore();
                if (ItemLores != null)
                    for (String LoreNow : ItemLores) {
                        if (LoreNow.contains(all) || LoreNow.contains(option))
                            e.setUseItemInHand(Event.Result.DENY);
                    }
            }
        }
    }

}
