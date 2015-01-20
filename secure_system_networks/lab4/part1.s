  40089b:	e8 f0 fd ff ff       	callq  400690 <fgets@plt>
  4008a0:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  4008a4:	48 83 c0 08          	add    $0x8,%rax
  4008a8:	c6 00 00             	movb   $0x0,(%rax)
  4008ab:	8b 45 fc             	mov    -0x4(%rbp),%eax
  4008ae:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  4008b2:	ba 08 00 00 00       	mov    $0x8,%edx
  4008b7:	48 89 ce             	mov    %rcx,%rsi
  4008ba:	89 c7                	mov    %eax,%edi
  4008bc:	e8 51 00 00 00       	callq  400912 <fflush@plt+0x232>
  4008c1:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  4008c5:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  4008c9:	ba 08 00 00 00       	mov    $0x8,%edx
  4008ce:	48 89 ce             	mov    %rcx,%rsi
  4008d1:	48 89 c7             	mov    %rax,%rdi
  4008d4:	e8 97 fd ff ff       	callq  400670 <strncmp@plt>
  4008d9:	89 45 f8             	mov    %eax,-0x8(%rbp)
  4008dc:	83 7d f8 00          	cmpl   $0x0,-0x8(%rbp)
  4008e0:	75 0c                	jne    4008ee <fflush@plt+0x20e>