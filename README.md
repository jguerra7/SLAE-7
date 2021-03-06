> This repository has been created for completing the requirements of the SecurityTube Linux Assembly Expert certification: http://securitytube-training.com/online-courses/securitytube-linux-assembly-expert/ Student ID: SLAE-1228

# SLAE32 course review
**TL;DR**: [SLAE32 course](http://www.securitytube-training.com/online-courses/securitytube-linux-assembly-expert/index.html) is great and you should do it if you are a beginner/intermediate. A little bit outdated but still absolutely valid. A piece of art for the price charged.

I have finally completed the SLAE32 course and certification by Security Training a few months after purchasing it. This review reflects solely my very own experience and should not be taken for granted by anyone.

## What to expect
SLAE32 is a course about x86 shellcodes. Not pwn, reverse engineering, malware analysis, CTFs or anything alike. Most of the course goes about writing x86 assembly code and debugging it, along with techniques to encode and encrypt shellcodes.

It is divided in 2 modules:
* **Module 1** - walks you through most of the juicy x86 instructions in a very effective way. It might be considered a comprehensible introduction to assembly and is the basis for the next module.
* **Module 2** - begins with a simple *exit()* shellcode then goes through the JMP-CALL-POP technique, encoders, polymorhphism, shellcode analysis and crypters.

Both parts are totally hands-on focused. There has not been a single moment I did not had both my video player and a terminal open. I followed line-by-line the instructions Vivek typed but not limiting to it. I also tried more modern encoders, read Phrack articles and broke stuff in unintend ways. I think this is how the course should be taken, allowing yourself to explore the introduced concepts in an empirical manner.

I have also received for free the GDB course by Security Training. I have not checked it out since I believed my GDB skills were enough for completing SLAE. Nevertheless, I have been told it is an awesome introduction to debuggers.

## Who should take it?
I do not see it as an advanced course although it covers a topic most beginners are generally not used to. Some previous x86 knowledge would be nice and C experience would not hurt. A reasonable understanding of compiling/assmblying/linking processes would also help, along with knowledge about how the stack works. All in all, it is a beginner focused course and with enough time and dedication anyone should be able to complete it. As the official site states:

    This course starts from the very basics of programming in Assembly Language and does not expect students to have prior programming experience.

## Certification
This is was a really neat surprise for me. I never acquired the course for the certification, but for the knowledge itself. However, having a concrete goal is great for keeping the focus and not quitting for any reason. After all, I had already invested $100+ and not getting the certification would make this a wasted money.

The certification format is unusual, which has positive and negative aspects. First of all, it is an open exam. The last video of module 2 presents the 7 assignments one must complete. There is no time for finishing them or a strict answer template. Even more curious, you must publish all the assignments online! So yeah, everybody else's exams are there if you want to snoop around.

I must say at first I did not like this model of certification. I thought it might be a good idea but would certainly nullify the certification value, since it could not guarantee that the examinee really did everything on his own instead of just cheating. It happens the proposed assignments were very well chosen. Considering that the Security Training staff checks the assignments, even if the candidate took a look at other students previous exams it would not invalidate his answer. The
assignments are complex and long in a way that even reproducing someone's answer would prove a certain degree of knowledge and effort.

One way or the other, with so much this course has to offer I do not think you should care all that much about whether the certification itself might get you that dream job or not. However, you should **absolutely** do it. This was the best part for me as I learned more with the assignments then with all the videos. It took me about 2 weeks studying about 3 everyday in order to finish it. Totally worth it.

Another interesting aspect of the exam is that it forces you to write, blog and have a GitHub account. I know it takes time to document your steps and most people in our field consider it boring. But trust me, it is a real treasure to have your intellectual development process written down. It helps you to put things together in your mind, serves as a future source and also helps people around. How much have you not learned from blog posts after all?

Not focusing on its market value, is what makes this certification great. Most highly valuable certs must have a strict format in order to keep their value. I do not think most people who take this course are doing it for the cert value (I did not at least). Indeed, this allows you to explore more while not loosing yourself in the abundant ocean of knowledge available.

## Isn't it old and outdated?
Not at all! This was one of my worries when I first started the course. I mean, the videos obvious show their age. The course uses Backtrack instead of Kali. Msfpayload instead of Msfvenom. Video quality is somewhat low. Audio quality too (with some funny/annoying background sounds depending on your mood). And yes, it is focused mostly in x86 and OSs without many protections, so do not expect to be coding shellcodes for your top notch Win10. There are other courses by Security Academy more focused on that.

For the record, I did the whole course in my x64 Debian 9 and fully upgraded Kali. Smooth.

That said, I would like to state none of the caveats above were significant to my learning. I can peacefully say I have learned A LOT of useful information. The bottom line is you must crawl before running. This is totally true and not different for this course. If you do not understand the basics of shellcoding in a simple WinXP how do you expect to bypass all those fancy ML-based security solutions?
