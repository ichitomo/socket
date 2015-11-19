require 'socket'

host = if ARGV[0] then ARGV[0] else 'localhost' end
port = if ARGV[1] then ARGV[1] else 'echo' end
sock = TCPSocket.open(host, port)

while msg = STDIN.gets
      print("you writed:", msg)
      #socketに書き込む
      sock.write(msg)
      #サーバから返ってきたメッセージを表示する。
      print("return message:", sock.gets)
      print("\n")
end
sock.close

