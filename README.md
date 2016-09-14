# alicebot

C++ code example of telegram bot api. Use it `as is`. E-mail address for questions is ivorob[at]gmail.com.

The `example` directory contains a few examples of using telegram bot api. To compile library or examples use the following commands:
`cmake . && make`

To compile on Windows platform you can use the following commands below, but now I'm not sure that code will be compiled correctly. I didn't try to compile this api on Windows. This feature is in TODO-list.
`cmake -G "NMake Makefiles"`
`nmake`

## Supported types
- User
- Message
- File
- PhotoSize

## Supoported methods
- sendMessage
- getFile
- getUpdates

## TODO
- Work with files
- Work with images
- Windows building
- Support of `getMe` method
- Support of `forwardMessage` method
- Support of `sendAudio` method
- Support of `sendDocument` method
- Support of `sendSticker` method
- Support of `sendVideo` method
- Support of `sendVoice` method
- Support of `sendLocation` method
- Support of `sendVenue` method
- Support of `sendContact` method
- Support of `sendChatAction` method
- Support of `getUserProfilePhotos` method
- Support of `kickChatMember` method
- Support of `leaveChat` method
- Support of `unbanChatMember` method
- Support of `getChat` method
- Support of `getChatAdministrators` method
- Support of `getChatMembersCount` method
- Support of `getChatMember` method
- Support of `answerCallbackQuery` method
- Support of `editMessageText` method
- Support of `editMessageCaption` method
- Support of `editMessageReplyMarkup` method
