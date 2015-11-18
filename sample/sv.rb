require 'socket'

port = if ARGV[0] then ARGV[0] else 'echo' end
gate = TCPServer.open(port)

sock = gate.accept
gate.close

while msg = sock.gets
      print("you get:", msg)
      line = msg.chomp
      if line == "tako"
        sock.write(line+"x"+"\n")
      else
        sock.write(line+"z"+"\n")
      end
end
sock.close

