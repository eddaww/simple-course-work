package handler;

import dao.BlockedUserDao;
import dao.UserDao;
import dto.BlockedUserDto;
import handler.AuthFilter.AuthResult;
import org.bson.Document;
import request.ParsedRequest;
import response.HttpResponseBuilder;
import response.RestApiAppResponse;

import java.util.List;

public class BlockUserHandler implements BaseHandler {

    @Override
    public HttpResponseBuilder handleRequest(ParsedRequest request) {
        BlockedUserDto blockDto = GsonTool.gson.fromJson(request.getBody(), BlockedUserDto.class);
        BlockedUserDao blockDao = BlockedUserDao.getInstance();
        UserDao userDao = UserDao.getInstance();

        AuthResult authResult = AuthFilter.doFilter(request);
        if (!authResult.isLoggedIn) {
            return new HttpResponseBuilder().setStatus(StatusCodes.UNAUTHORIZED);
        }

        if (userDao.query(new Document("userName", blockDto.getBlocked())).size() == 0) {
            var res = new RestApiAppResponse<>(false, null, "Blocking unknown user");
            return new HttpResponseBuilder().setStatus("200 OK").setBody(res);
        }
        blockDao.blockUser(authResult.userName, blockDto.getBlocked());
        var res = new RestApiAppResponse<>(true, List.of(blockDto), null);
        return new HttpResponseBuilder().setStatus("200 OK").setBody(res);
    }
}