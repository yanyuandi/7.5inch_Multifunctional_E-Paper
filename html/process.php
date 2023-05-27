<?php
    include 'db.php';

    // 处理提交留言请求
    if ($_POST['action'] == 'add') {
       // $name = $_POST['name'];
        $sql = "SELECT COUNT(*) as count FROM daiban";
        $result = $conn->query($sql);

    if ($result) {
        $row = $result->fetch_assoc();
        $count = $row['count'];
    
    // 如果记录数大于等于6，则禁止添加新待办事项并弹出提醒
    if ($count >= 10) {
        echo "<script>alert('已达到最多10条待办事项');window.location.href='index.php';</script>";
        
    } else {
        // 否则，插入新的待办事项
        $thing = $_POST['thing'];
        $sql = "INSERT INTO daiban (thing) VALUES ('$thing')";
        if ($conn->query($sql) === TRUE) {
            header("Location: index.php");
        } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    }
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}
}
    // 处理删除留言请求
    if ($_GET['action'] == 'delete') {
        $id = $_GET['id'];

        $sql = "DELETE FROM daiban WHERE id=$id";

        if ($conn->query($sql) === TRUE) {
            header("Location: index.php");
        } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    }

    // 处理设为精选请求
    if ($_GET['action'] == 'isimp') {
        $id = $_GET['id'];

        $sql = "UPDATE daiban SET isimp=1 WHERE id=$id";

        if ($conn->query($sql) === TRUE) {
            header("Location: index.php");
        } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    }

    // 处理取消设为精选请求
    if ($_GET['action'] == 'notimp') {
    $id = $_GET['id'];

    $sql = "UPDATE daiban SET isimp=0 WHERE id=$id"; // 将isimp字段更新为0

    if ($conn->query($sql) === TRUE) {
        header("Location: index.php");
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
    }

       // 完成
    if ($_GET['action'] == 'isdone') {
    $id = $_GET['id'];

    $sql = "UPDATE daiban SET isdone=1 WHERE id=$id"; // 将isimp字段更新为0

    if ($conn->query($sql) === TRUE) {
        header("Location: index.php");
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
    }

          // 未完成
    if ($_GET['action'] == 'notdone') {
    $id = $_GET['id'];

    $sql = "UPDATE daiban SET isdone=0 WHERE id=$id"; // 将isimp字段更新为0

    if ($conn->query($sql) === TRUE) {
        header("Location: index.php");
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
    }


    $conn->close();
?>