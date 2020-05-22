package enjcat.priventbylore;

import org.bukkit.command.Command;
import org.bukkit.command.CommandExecutor;
import org.bukkit.command.CommandSender;

public class command implements CommandExecutor {
    @Override
    public boolean onCommand(CommandSender sender, Command command, String label, String[] args) {
        if(args.length > 0){
            if(args[0].equals("on")){
                sender.sendMessage("아이템 움직임이 제한됩니다.");
                PriventByLore.onoff = true;
            }
            else if(args[0].equals("off")){
                sender.sendMessage("아이템을 자유롭게 움직입니다.");
                PriventByLore.onoff = false;
            }

        }
        return true;
    }
}
