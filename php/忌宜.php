<?php
// 设置时区为东八区
date_default_timezone_set('Asia/Shanghai');
// 获取当前日期
$date = date('Y-m-j');
// 对日期进行格式化，确保月份和日份的格式都是一位数的
$date = sprintf('%d-%d-%d', ...explode('-', $date));


// API地址
$url = 'https://api.topthink.com/calendar/day?appCode=这里替换你的秘钥&date=' . $date;

// 初始化cURL
$ch = curl_init();

// 设置cURL参数
curl_setopt($ch, CURLOPT_URL, $url);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false); // 忽略SSL证书验证

// 发送请求并获取响应数据
$response = curl_exec($ch);

// 关闭cURL
curl_close($ch);

// 解析JSON数据
$data = json_decode($response, true);

// 判断suit是否存在，如果存在则将其中的"."替换为空格，并截取前14个字符
if (isset($data['data']['suit'])) {
    $data['data']['suit'] = mb_substr(str_replace(".", " ", $data['data']['suit']), 0, 14, 'UTF-8');
}

// 判断avoid是否存在，如果存在则将其中的"."替换为空格，并截取前14个字符
if (isset($data['data']['avoid'])) {
    $data['data']['avoid'] = mb_substr(str_replace(".", " ", $data['data']['avoid']), 0, 14, 'UTF-8');
}

// 编码JSON数据并进行UTF-8编码转换
$json = json_encode($data, JSON_UNESCAPED_UNICODE);
$json = iconv("UTF-8", "UTF-8//IGNORE", $json);

// 检查JSON编码是否出错
if (json_last_error() !== JSON_ERROR_NONE) {
    echo 'JSON编码出错：' . json_last_error_msg();
} else {
    // 输出JSON数据
    echo $json;
}