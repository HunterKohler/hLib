<?php

$usr = "username";
$user = mysqli_escape_string(NULL,$usr);
$query = "SELECT * from users where username='$user'";
echo $query;
