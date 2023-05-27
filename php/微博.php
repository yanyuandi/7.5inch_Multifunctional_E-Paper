<?php

// 1. 使用 cURL 获取 JSON 数据
$url = "https://weibo.com/ajax/side/hotSearch";
$ch = curl_init();
curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_URL, $url);
$result = curl_exec($ch);
curl_close($ch);

// 2. 解析 JSON 数据，筛选出需要的数据
$data = json_decode($result, true); // 将 JSON 字符串解码为 PHP 关联数组
$realtime_words = $data["data"]["realtime"]; // 只获取"data"数组中的"realtime"数组

$words_assoc = array(); // 保存每个"word"键和对应值的关联数组

foreach ($realtime_words as $key => $word) {
    if ($key >= 34) { // 当遍历到第21个元素时退出循环
        break;
    }
    $words_assoc[] = [
		"word" => mb_substr($word["word"], 0, 12, "UTF-8"), // 截取word键的前6个字符作为输出
        "label_name" => isset($word["label_name"]) ? $word["label_name"] : ""
    ];
}

// 3. 添加 code 值，并重新组装 JSON 数据并输出
$output_arr = [ "code" => 200, "data" => $words_assoc ];
$output_json = json_encode($output_arr, JSON_UNESCAPED_UNICODE | JSON_PRETTY_PRINT); // 将包含"word"键和"label_name"键的关联数组编码为 JSON 字符串，并保留中文字符和缩进
echo $output_json;

