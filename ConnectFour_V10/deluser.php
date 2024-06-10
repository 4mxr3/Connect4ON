<?php
include("./includes/user.php");
if ($_SERVER["REQUEST_METHOD"] != "POST") {
    header("Location: ./index.php");
}
$currUser = new User();
$currUser->fillFromSql($_POST["u"], $_POST["p"]);
$currUser->delFromSql();

header("Location: ./allusers.php");