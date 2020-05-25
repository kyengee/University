package enjcat.saveloc;

import org.bukkit.Location;
import org.bukkit.Material;
import org.bukkit.command.Command;
import org.bukkit.command.CommandSender;
import org.bukkit.event.EventHandler;
import org.bukkit.event.Listener;
import org.bukkit.event.block.BlockBreakEvent;
import org.bukkit.event.block.BlockPlaceEvent;
import org.bukkit.event.entity.ItemSpawnEvent;
import org.bukkit.event.player.PlayerInteractEvent;
import org.bukkit.plugin.java.JavaPlugin;

import java.io.File;
import java.io.FileWriter;
import java.util.*;

public final class Saveloc extends JavaPlugin implements Listener {

    String Filename;
    List<String> loclist;

    @Override
    public void onEnable() {
        // Plugin startup logic
        this.loclist = new ArrayList<>();

        String path = "./plugins/좌표저장"; //폴더 경로
        File Folder = new File(path);

        // 해당 디렉토리가 없을경우 디렉토리를 생성합니다.
        if (!Folder.exists()) {
            try{
                Folder.mkdir(); //폴더 생성합니다.
                System.out.println("좌표저장폴더가 생성되었습니다.");
            }
            catch(Exception e){
                e.getStackTrace();
            }
        }else {
            System.out.println("좌이미 좌표저장폴더가 생성되어 있습니다.");
        }

        getServer().getPluginManager().registerEvents(this, this);
    }

    @Override
    public boolean onCommand(CommandSender sender, Command command, String label, String[] args) {

        if(args.length > 0){
            if(args[0].equals("filename")){
                if(args[1] != null) {
                    sender.sendMessage("타겟파일을 " + args[1] +".txt 로 변경합니다.");
                    this.Filename = new String(args[1]);
                }
            }
            else if(args[0].equals("save")){
                try {
                    File f = new File("./plugins/좌표저장/"+Filename+".txt");
                    FileWriter fw = new FileWriter(f, true);
                    sender.sendMessage(Filename +"파일을 엽니다.");
                    for (String loc: this.loclist) {
                        fw.write(loc + "\r\n");
                    }
                    fw.flush();
                    fw.close();
                    sender.sendMessage(Filename +"파일을 저장했습니다.");
                    this.loclist.clear();

                }catch (Exception e){}
            }
            else if(args[0].equals("memo")){
                sender.sendMessage("List에 " + args[1] + " 를 추가합니다.");
                if(args[1] != null) {
                    this.loclist.add(args[1]);
                }
            }

        }
        return true;
    }

    @EventHandler
    public void onBlockBreak(BlockBreakEvent e) {
        if (e.getPlayer().getInventory().getItemInMainHand().getItemMeta().getDisplayName().equals("위치저장")) {
            e.getPlayer().sendMessage(e.getBlock().getWorld().getName() + ',' + (int) e.getBlock().getLocation().getX() + ',' +
                    (int) (e.getBlock().getLocation().getY()+1) + ',' + (int) e.getBlock().getLocation().getZ());
            this.loclist.add(e.getBlock().getWorld().getName() + ',' + (int) e.getBlock().getLocation().getX() + ',' +
                    (int) (e.getBlock().getLocation().getY()+1) + ',' + (int) e.getBlock().getLocation().getZ());
            Location a = new Location(e.getBlock().getWorld(), e.getBlock().getLocation().getX(), e.getBlock().getLocation().getY() - 1, e.getBlock().getLocation().getZ());
            a.getBlock().setType(Material.GOLD_BLOCK);
            a.getBlock().setTypeId(0)
        }
    }

    @EventHandler
    public void onblockPlaced(PlayerInteractEvent e){
        e.getBlockPlaced().getTypeId() == Material.GRASS Material.DIRT
            e.setCancelled(true);
        e.getClickedBlock().setTypeId(2)
        e.getBlockPlaced().getLocation().getX()
                e.getEntity().getEntityId()
                        e.setCancelled();
        e.setDropItems();e.getBlock().getTypeId()
                e.getAction(). Action.LEFT_CLICK_BLOCK
                        e.getAction().
    }

}
