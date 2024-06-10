<?php
include("./includes/user.php");
session_start();
$_SESSION["loginErr"] = "";
$currUser = new User();
$result = $currUser->fillFromSql($_SESSION["user"], $_SESSION["pass"]);

if ($result == -1){
    //If not user found, set login error message
    $_SESSION["loginErr"] = "No user with that username and password";
    //Send back to main page
    header("Location: ../index.php");
}
?>

<?php
include("./includes/header.php");
?>

<div id="response">
    <?php
        echo $currUser->printStats();
    ?>
</div>

<?php
include("./includes/footer.html");
?>