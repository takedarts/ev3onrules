EV3onRules とは
---------------

EV3onRulesはToppers/EV3RT上で動作するルールベースフレームワークです。

EV3RTを使うことで、ETロボコンの公式ロボットであるEV3wayの制御プログラム
を開発することができます。 しかし、EV3RTは基本的な制御機能の提供を目的と
しているため、複雑な制御プログラムを開発する場合は独自のフレームワークを
実装する必要がありました。 EV3onRulesでは、EV3wayを動作させるために最低
限必要となる動作プログラムを実装しており、これ以外に必要となる機能をルー
ルとして実装する方式を採用しています。 これにより、プログラム開発者は個
々の場面に対応するためのルールを実装するだけでよくなり、機能実装や制御ア
ルゴリズムに集中して実装することができます。 また、制御動作の変化をルー
ルチェインとして実装しますので、動作の変更や機能の再利用も容易となってい
ます。

動作環境
--------

EV3onRulesはWindowsのcygwinとMax OS Xで動作確認をしています。

Linuxでも、おそらく動作すると思います。

ダウンロード
------------

EV3onRulesはToppers/EV3RT上で動作します。

まずは、Toppers/EV3RTのWebサイトからEV3RTをダウンロードし、EV3RTで開発で
きる環境を整えてください。

次に、EV3onRulesをダウンロードします。 対応するEV3RTのバージョンが異なり
ますので、注意してください。

開発環境の構築
--------------

ダウンロードしたEV3onRulesのアーカイブを任意のディレクトリに展開します。

このアーカイブを展開したディレクトリ内でプログラムを開発することになります。

展開したファイルの中に「Makefile」が含まれています。 この「Makefile」内
の変数`EV3RT_DIR`にToppers/EV3RTのソースファイル(hrp2)のパスを設定します。
例えば、`/opt/hrp2`以下にEV3RTのソースファイルを展開している場合、Makefile
の10行目は以下のようになります。

    EV3RT_DIR := /opt/hrp2

アプリケーションの開発
----------------------

プログラムを作成し、アプリケーションを構築します。

プログラムの作成方法については、WikiのチュートリアルやAPIドキュメントを参
考にしてください。

Wikiのチュートリアル: https://github.com/takedarts/ev3onrules/wiki
APIドキュメント: https://takedarts.github.io/ev3onrules/apidoc/1.0/

次に、作成したプログラムをコンパイルし、アプリケーションを構築します。
cygwin-terminalなどのコマンド入力画面から`make`を実行してください。 makeに
成功すると、アプリケーションファイル「app」が生成されます。 これはEV3RTアプ
リケーションとなっていますので、Toppers/EV3RTのWebサイトにある説明に従って
LEGO Mindstorms EV3にインストールしてください。

    % make
    perl /workspace/EV3onRules/util/list.pl
    perl /workspace/EV3onRules/util/factory.pl
    perl /workspace/EV3onRules/util/include.pl
    perl /workspace/EV3onRules/util/config.pl
    make[1]: Entering directory '/workspace/EV3onRules/build'
      CFG[1]  module_cfg.h
      CFG[2]  module_cfg.h
    make[1]: Leaving directory '/workspace/EV3onRules/build'
    make[1]: Entering directory '/workspace/EV3onRules/build'
      CC      module_cfg.c
      CC      ev3api_cfg.c
      CXX     ../src/app.cpp
      CXX     ../src/Controller.cpp
    ...
      LD      app
    make[1]: Leaving directory '/workspace/EV3onRules/build'
    cp -f build/app app

ドキュメント
------------

- Wiki: https://github.com/takedarts/ev3onrules/wiki
- API: https://takedarts.github.io/ev3onrules/apidoc/1.0/

ライセンス
----------

EV3onRulesのライセンスはGPL2.0となります。

免責事項
--------

EV3onRulesの開発者及び配布者は、EV3onRulesを使用することによって生じるいかな
る損害に対しても一切責任を負いません。

質問・バクレポートなど
----------------------

質問等がありましたら、開発者(武田敦志: takeda[at]cs.tohoku-gakuin.ac.jp)までお知らせください。

謝辞
----

EV3onRulesは東北学院大学個別研究「物理シミュレータと自律ロボットを活用した
ソフトウェア開発教育に関する研究」の成果物の一部です。
