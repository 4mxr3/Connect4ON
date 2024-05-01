<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>Connect 4</title>
        <?php include 'Game.php' ;?>
    </head>
    <body>
        <?php
        
         $bin;
         $game1 = new Game();
        
        $results = bin.login();
        
        switch(results)
        {
            case 1:
                //ADMIN lOGIN
                bin.adminMenu();
                break;
            case 2:
                //USER LOGIN
               $game1(bin);
                break;
            
            default :
                echo "<p>Error logging in. Exiting Program</p>";
                break;
        }
        
        ?>
    </body>
</html>
