<?php
    // 连接数据库
    $conn = new mysqli('你的服务器数据库地址', 'root', '数据库密码', '数据表名');

    if ($conn->connect_error) {
        die("连接失败: " . $conn->connect_error);
    }
?>