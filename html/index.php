<!DOCTYPE html>
<html>
<head>
	<title>待办事件提交</title>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=0.8">
	<meta name="viewport" content="width=device-width, initial-scale=0.8, maximum-scale=0.8, user-scalable=no">
	<link rel="stylesheet" type="text/css" href="style.css">
		<script>
		window.onload = function() {
			// 获取视窗宽度
			var windowWidth = window.innerWidth || document.documentElement.clientWidth || document.body.clientWidth;
			console.log("视窗宽度为：" + windowWidth + " 像素");

			// 获取文档宽度
			var documentWidth = document.documentElement.clientWidth || document.body.clientWidth;
			console.log("文档宽度为：" + documentWidth + " 像素");
		}
	</script>
</head>
<body>
	<h1>待办事件E-Paper</h1>
	<form method="post" action="process.php">
		<!-- <label for="name">姓名：</label>
		<input type="text" name="name" id="name"><br><br> -->
		<!-- <label for="thing">待办事件内容：</label> -->
		<input name="thing" id="thing" rows="1" maxlength="10" autofocus=true placeholder="待办事件限制13个文字" required=true></input>
		<button type="submit" name="action" value="add">提交待办事件</button>
	</form>
	<hr>
	<div class="weather">
	<?php
			include 'db.php';
	// 查询所有留言
	//$sql = "SELECT * FROM daiban ORDER BY create_time DESC";
	$sql = "SELECT * FROM daiban";
	$result = $conn->query($sql);
	if ($result->num_rows > 0) {
		// 输出每个待办事件
		$count = 0;
		while($row = $result->fetch_assoc()) {
			//echo "<p>{$row['thing']}";
			$count++;
			$style = '';
			if ($row['isimp']) {
				$style .= 'color:red;';
			}
			if ($row['isimp'] && $row['isdone']) {
				$style .= 'text-decoration:line-through;color:red;';
			} elseif ($row['isdone']) {
				$style .= 'text-decoration:line-through;';
			}
			echo "<div style=\"text-align: left;\"><p style=\"$style\">{$count}. {$row['thing']}</p>";
			echo " <button onclick=\"location.href='process.php?action=delete&id={$row['id']}'\">	删除</button> ";
			if($row['isimp']) {
				echo "<span><button style=\"color:red;\" onclick=\"	location.href='process.php?action=notimp&id={$row['id']}'\">重要</button></span>";
			} else {
				echo "<button onclick=\"location.href='process.php?action=isimp&id={$row['id']}'\">	设为重要事件</button>";
			}
			if ($row['isdone']) {
				// 如果已完成，则显示“已完成”按钮
				echo " <button onclick=\"location.href='process.php?action=notdone&id={$row['id']}'\">	已完成</button>";
			} else {
				// 否则，显示“设为已完成”按钮
				echo " <button onclick=\"location.href='process.php?action=isdone&id={$row['id']}'\">	设为已完成</button>";
			}
			echo "</div>";
			//	echo "<hr>";
		}
	} else {
		echo "<p>暂无待办事件</p>";
	}
	$conn->close();
	?>
	</div>
</body>
</html>




