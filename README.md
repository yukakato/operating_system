# オペレーティングシステム講義用
### コンパイル方法（pthread）

`gcc -o thread thread.c -lpthread`

### ファイル構成
- fork.c: 新しいプロセスの生成
- ls_test.c: 新しいファイルを読み込んで実行
- thread.c: スレッドプログラミングの基本形
- mutex-nolock.c: マルチスレッド（ロックなし）
- mutex-lock.c: マルチスレッド（ロックあり）
- semaphore.c: セマフォ
- condv-buffer.c: 条件変数
- Producer_Consumer_Monitor.java: モニタ
